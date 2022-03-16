#include "PLXStreamReader.h"
#include <iostream>
namespace plasma {
	PLXStreamReader::PLXStreamReader(Engine* engine, PageInfo* pageInfo, Node* targetNode, u32 fileFlags, std::ifstream* stream, std::vector<u64> keys) 
		: StreamReader(stream) {
		m_fileFlags = fileFlags;
		m_keys = keys;
		m_targetNode = targetNode;
		m_engine = engine;
		m_pageInfo = pageInfo;
	}

	void PLXStreamReader::Read() {
		if (m_fileFlags & (u32)FLAGS::CHECK_FORMAT) {
			std::streampos pos = m_stream->tellg();
			ReadI32();
			ReadI32();
			ReadI32();
			ReadI32();

			char correctHeader[] = "PlasmaGraphics";
			char header[sizeof(correctHeader)] = { 0 };

			m_stream->read(header, sizeof(correctHeader) - 1);
			m_stream->seekg(SEEK_SET);
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
		}
	}

	std::string PLXStreamReader::ParseChunkHeader() {
		i32 chunkID = ReadI32();

		if (chunkID == 0) {
			// Needs a name definition block

		}

	}
};