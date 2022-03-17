#include "PLXStreamReader.h"
#include <iostream>
namespace plasma {
	PLXStreamReader::PLXStreamReader(Engine* engine, PageInfo* pageInfo, Node* targetNode, u32 fileFlags, std::ifstream* stream, std::vector<u64> keys) 
		: ChunkStreamReader(stream) {
		m_fileFlags = fileFlags;
		m_keys = keys;
		m_targetNode = targetNode;
		m_engine = engine;
		m_pageInfo = pageInfo;
	}

	void PLXStreamReader::Read() {
		if (m_fileFlags & (u32)FLAGS::CHECK_FORMAT) {
			std::streampos pos = m_stream->tellg();

			ReadVal<i32>();
			ReadVal<i32>();
			ReadVal<i32>();
			ReadVal<i32>();

			char correctHeader[] = "PlasmaGraphics";
			char header[sizeof(correctHeader)] = { 0 };

			m_stream->read(header, sizeof(correctHeader) - 1);
			m_stream->seekg(pos);
			//std::cout << header << std::endl;

			std::string str_correctHeader = correctHeader;
			std::string str_header = header;

			if (str_header != str_correctHeader) {
				//TODO: throw an exception
				std::cout << "PLX header invalid." << std::endl;
			}
		}

		m_obfuscationHash = 0;
		while (m_stream->peek() != EOF) {
			std::string chunkName = ParseChunkHeader();
			std::cout << "Chunk: " << chunkName << std::endl;

			ParseChunkLength(); // this is in the chunk specific blocks in plasma

			if (chunkName == "PlasmaGraphics") {
				ReadPlasmaGraphics();
			}
			else if (chunkName == "Seal") {
				bool validLicense = ReadSeal();

				if (!validLicense) {
					//TODO: throw exception
					std::cout << "License key invalid" << std::endl;
				}
			}

			// This is for testing, not originally a plasma feature
			if (m_chunkEnds.size() > 0) {
				std::streampos next = m_chunkEnds.front();
				if (next == -1) break;
				std::cout << next << std::endl;
				m_chunkEnds.pop_front();
				m_stream->seekg(next);
			}
		}
	}

	std::string PLXStreamReader::ParseChunkHeader() {
		i32 chunkID = ReadVal<i32>();

		if (chunkID == 0) {
			// Needs a name definition block
			ParseChunkLength();
			i32 newChunkID = ReadVal<i32>();
			std::string newChunkName = "";
			bool unobfuscated = m_obfuscationHash == 0;

			if (unobfuscated) {
				newChunkName = ReadString();
			}
			else {
				newChunkName = ReadObfuscatedString();
			}

			m_chunkTypeNames[newChunkID] = newChunkName;

			NextChunk();

			chunkID = ReadVal<i32>();
			
		}

		return m_chunkTypeNames[chunkID];
	}

	void PLXStreamReader::ReadPlasmaGraphics() {
		u32 version = ReadVal<u32>();
		std::cout << "PlasmaGraphics version " << version << std::endl;
		if (version > 1) {
			//TODO: throw exception
			std::cout << "PLX wrong version" << std::endl;
		}
		NextChunk();
	}

	bool PLXStreamReader::ReadSeal() {
		bool validLicense = false;
		std::vector<u64> keysToTry = m_keys;

		// Two default keys
		keysToTry.push_back(0);
		keysToTry.push_back(StringHash("PlasmaGraphics"));

		std::string magic = "PlasmaGraphics";
		std::vector<char> obfuscatedMagic = ReadByteArray();

		for (u64 key : keysToTry) {
			std::string deobfuscatedMagic = DeobfuscateString(obfuscatedMagic, key);
			if (deobfuscatedMagic == magic) {
				m_obfuscationHash = key;
				validLicense = true;
			}
		}

		NextChunk();
		return validLicense;
	}
};