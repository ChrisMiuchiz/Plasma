#include "ChunkStreamReader.h"
#include <iostream>

namespace plasma {
	u64 StringHash(std::string s) {
		u64 h = 0x3ffffffffffe5;
		for (u32 i = 0; i < s.size(); i++) {
			h = 31 * h + s[i];
		}
		return h;
	}

	ChunkStreamReader::ChunkStreamReader(std::ifstream* stream) {
		m_stream = stream;
	}

	void ChunkStreamReader::ParseChunkLength() {
		u32 length = ReadVal<u32>();
		std::streampos pos = m_stream->tellg();
		std::streampos chunkEnd = pos + std::streamoff(length);
		m_chunkEnds.push_back(chunkEnd);
	}

	std::string ChunkStreamReader::ReadString() {
		u32 size = ReadVal<u32>();
	
		// An additional check for UINT32_MAX has been added here
		if (size != 0 && size != UINT32_MAX) {
			char* buffer = new char[size + 1];
			buffer[size] = '\0';
			m_stream->read(buffer, size);
			std::string result(buffer);
			delete[] buffer;
			return result;
		}

		return "";
	}

	std::vector<char> ChunkStreamReader::ReadByteArray() {
		u32 size = ReadVal<u32>();
		std::vector<char> result;
		result.resize(size);

		m_stream->read(result.data(), size);

		return result;
	}

	bool ChunkStreamReader::NextChunk() {
		if (!m_stream->eof()) {
			if (m_chunkEnds.front() != m_stream->tellg()) {
				// Have not consumed entire chunk
				std::cout << "Have not finished entire chunk!" << std::endl;
				return false;
			}
		}

		m_chunkEnds.pop_front();
		return true;
	}

	void ChunkStreamReader::DeobfuscateString(char* buffer, u32 length, char* obfuscationKey) {
		u32 startingValue = *(u32*)&obfuscationKey[0];
		u32 keyOffset = startingValue % length;
		std::vector<char> output;
		output.resize(length);

		for (u32 i = 0; i < length; i++) {
			u32 outIdx = (keyOffset + i) % length;
			u32 keyIdx = (outIdx % 8);
			u32 valOffset = obfuscationKey[keyIdx];
			output[outIdx] = buffer[i] - valOffset;
		}

		memcpy(buffer, output.data(), length);
	}
};