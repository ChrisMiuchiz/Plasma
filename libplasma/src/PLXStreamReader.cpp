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
		while (!m_stream->eof()) {
			std::string chunkName = ParseChunkHeader();
			std::cout << "Chunk: " << chunkName << std::endl;

			ParseChunkLength();
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
				if (newChunkName == "Seal") m_obfuscationHash = StringHash("PlasmaXGraphics"); // REMOVE ME
			}
			else {
				// Do the deobfuscation
				std::vector<char> obfuscatedBytes = ReadByteArray();
				std::cout << "obfuscatedBytes size " << obfuscatedBytes.size() << std::endl;
				DeobfuscateString(obfuscatedBytes.data(), obfuscatedBytes.size(), (char*)&m_obfuscationHash);
				obfuscatedBytes.push_back('\0'); // Not exactly how plasma does this
				newChunkName = obfuscatedBytes.data();
			}

			m_chunkTypeNames[newChunkID] = newChunkName;

			NextChunk();

			chunkID = ReadVal<i32>();
			
		}

		return m_chunkTypeNames[chunkID];
	}
};