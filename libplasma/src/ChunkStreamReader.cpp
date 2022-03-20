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

	// Reads the length of a chunk and then remembers it. Won't be allowed to
	// leave a chunk until the entire chunk has been read. Chunks can be
	// entered in a nested fashion.
	void ChunkStreamReader::EnterChunk() {
		u32 length = ReadVal<u32>();
		std::streampos pos = m_stream->tellg();
		std::streampos chunkEnd = pos + std::streamoff(length);
		m_chunkEnds.push_front(chunkEnd);
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

	std::wstring ChunkStreamReader::ReadWString() {
		u32 size = ReadVal<u32>();

		// An additional check for UINT32_MAX has been added here
		if (size != 0 && size != UINT32_MAX) {
			wchar_t* buffer = new wchar_t[size + 1];
			buffer[size] = '\0';
			char* rawData = (char*)buffer;
			u32 rawSize = size * sizeof(wchar_t);
			m_stream->read(rawData, rawSize);
			std::wstring result(buffer);
			delete[] buffer;
			return result;
		}

		return L"";
	}

	std::string ChunkStreamReader::ReadObfuscatedString() {
		std::vector<char> obfuscatedBytes = ReadCharArray();
		DeobfuscateString(obfuscatedBytes.data(), obfuscatedBytes.size(), (char*)&m_obfuscationHash);
		obfuscatedBytes.push_back('\0'); // Not exactly how plasma does this
		return obfuscatedBytes.data();
	}

	std::vector<char> ChunkStreamReader::ReadCharArray() {
		u32 size = ReadVal<u32>();
		std::vector<char> result;
		result.resize(size);

		m_stream->read(result.data(), size);

		return result;
	}

	std::vector<u8> ChunkStreamReader::ReadByteArray() {
		u32 size = ReadVal<u32>();
		std::vector<u8> result;
		result.resize(size);

		m_stream->read((char*)result.data(), size);

		return result;
	}

	// Returns true if the chunk is allowed to be left (fully read).
	// Returning false indicates that there is still more to read before it is
	// allowed to exit the chunk.
	bool ChunkStreamReader::FinishChunk() {
		if (!m_stream->eof()) {
			if (m_chunkEnds.front() != m_stream->tellg()) {
				// Have not consumed entire chunk
				//std::cout << "Have not finished entire chunk!" << std::endl;
				return false;
			}
		}

		m_chunkEnds.pop_front();
		return true;
	}

	void ChunkStreamReader::SkipChunk() {
		u32 chunkSize = ReadVal<u32>();
		std::streampos position = m_stream->tellg();
		m_stream->seekg(position + std::streamoff(chunkSize));
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

	std::string ChunkStreamReader::DeobfuscateString(const std::vector<char>& bytes, u64 key) {
		u32 stringSize = bytes.size();
		u64 bufferSize = stringSize + 1;
		char* buffer = new char[(size_t)bufferSize];
		memcpy(buffer, bytes.data(), bytes.size());
		u64 obfuscationKey = key;

		DeobfuscateString(buffer, stringSize, (char*)&obfuscationKey);

		buffer[stringSize] = '\0';

		std::string result = buffer;

		delete[] buffer;

		return result;
	}
};