#include "PLXStreamReader.h"
#include <iostream>
#include "zlib.h"
#include "Texture.h"
#include "plutils.h"
#include "GLEngine.h"

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
			else if (chunkName == "Texture") {
				ReadTexture();
			}
			else {
				SkipChunk();
			}
		}
	}

	std::string PLXStreamReader::ParseChunkHeader() {
		i32 chunkID = ReadVal<i32>();

		if (chunkID == 0) {
			// Needs a name definition block
			EnterChunk();
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

			FinishChunk();

			chunkID = ReadVal<i32>();
			
		}

		return m_chunkTypeNames[chunkID];
	}

	bool PLXStreamReader::Decompress(const std::vector<u8>& input, std::vector<u8>& output) {
		// TODO: change how buffer is allocated
		bool result;
		u32 bufferSize = input.size() * 30;
		char* buffer = new char[bufferSize];
		Bytef* dest = (Bytef*)buffer;
		uLongf destLen = bufferSize;
		Bytef* source = (Bytef*)input.data();
		uLong sourceLen = input.size();
		int uncompressResult = uncompress(dest, &destLen, source, sourceLen);
		if (uncompressResult == Z_OK) {
			output.resize(destLen);
			memcpy(output.data(), dest, destLen);
			result = false;
		}
		else {
			output.clear();
			result = true;
		}

		delete[] buffer;
		return result;
	}

	void PLXStreamReader::ReadPlasmaGraphics() {
		EnterChunk();
		u32 version = ReadVal<u32>();
		std::cout << "PlasmaGraphics version " << version << std::endl;
		if (version > 1) {
			//TODO: throw exception
			std::cout << "PLX wrong version" << std::endl;
		}
		FinishChunk();
	}

	bool PLXStreamReader::ReadSeal() {
		bool validLicense = false;
		std::vector<u64> keysToTry = m_keys;

		EnterChunk();

		// Two default keys
		keysToTry.push_back(0);
		keysToTry.push_back(StringHash("PlasmaGraphics"));

		std::string magic = "PlasmaGraphics";
		std::vector<char> obfuscatedMagic = ReadCharArray();

		for (u64 key : keysToTry) {
			std::string deobfuscatedMagic = DeobfuscateString(obfuscatedMagic, key);
			if (deobfuscatedMagic == magic) {
				m_obfuscationHash = key;
				validLicense = true;
			}
		}

		FinishChunk();
		return validLicense;
	}

	void PLXStreamReader::ReadTexture() {
		EnterChunk();
		std::wstring textureName;
		i32 textureID = -1;
		Texture::Format textureFormat = { 1, 1, 1, 1 };
		u32 textureWidth = 0;
		u32 textureHeight = 0;
		std::vector<u8> pixelsData;

		if (FinishChunk()) return;

		do {
			std::string chunkName = ParseChunkHeader();

			std::cout << "Texture Chunk: " << chunkName << std::endl;
			//std::cin.get();

			if (chunkName == "Texture.name") {
				EnterChunk();
				textureName = StringToWstring(ReadString());
				FinishChunk();
			}
			else if (chunkName == "Texture.wname") {
				EnterChunk();
				textureName = ReadWString();
				FinishChunk();
			}
			else if (chunkName == "Texture.id") {
				EnterChunk();
				textureID = ReadVal<i32>();
				FinishChunk();
			}
			else if (chunkName == "Texture.format.pixelFormat") {
				EnterChunk();
				textureFormat.pixelFormat = ReadVal<i32>();
				FinishChunk();
			}
			else if (chunkName == "Texture.format.minFilter") {
				EnterChunk();
				textureFormat.minFilter = ReadVal<i32>();
				FinishChunk();
			}
			else if (chunkName == "Texture.format.maxFilter") {
				EnterChunk();
				textureFormat.maxFilter = ReadVal<i32>();
				FinishChunk();
			}
			else if (chunkName == "Texture.format.horizontalWrap") {
				EnterChunk();
				textureFormat.horizontalWrap = ReadVal<i32>();
				FinishChunk();
			}
			else if (chunkName == "Texture.format.verticalWrap") {
				EnterChunk();
				textureFormat.verticalWrap = ReadVal<i32>();
				FinishChunk();
			}
			else if (chunkName == "Texture.width") {
				EnterChunk();
				textureWidth = ReadVal<u32>();
				FinishChunk();
			}
			else if (chunkName == "Texture.height") {
				EnterChunk();
				textureHeight = ReadVal<u32>();
				FinishChunk();
			}
			else if (chunkName == "Texture.pixels") {
				EnterChunk();
				pixelsData = ReadByteArray();
				FinishChunk();
			}
			else if (chunkName == "Texture.compressedPixels") {
				EnterChunk();
				std::vector<u8> compressedPixels = ReadByteArray();
				Decompress(compressedPixels, pixelsData);
				FinishChunk();
			}
			else {
				SkipChunk();
			}

		} while (!FinishChunk());

		if (textureID != -1) {
			Texture* newTexture = m_engine->NewTexture(textureWidth, textureHeight, pixelsData.data(), textureFormat, textureName, false);
			m_textures[textureID] = newTexture;
		}
	}
};