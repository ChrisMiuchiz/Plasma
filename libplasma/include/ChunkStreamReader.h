#pragma once
#include <fstream>
#include "types.h"
#include <map>
#include <list>
#include <vector>

namespace plasma {
	u64 StringHash(std::string s);
	class ChunkStreamReader {
	public:
		friend class PLXStreamReader;
		ChunkStreamReader(std::ifstream* stream);
		void ParseChunkLength();
		std::string ReadString();
		std::string ReadObfuscatedString();
		std::vector<char> ReadByteArray();
		bool NextChunk();
		void DeobfuscateString(char* buffer, u32 length, char* obfuscationKey);
		std::string DeobfuscateString(const std::vector<char>& bytes, u64 key);

		template <typename T>
		T ReadVal() {
			T result = 0;
			m_stream->read((char*)&result, sizeof(result));
			return result;
		}

	private:
		std::list<std::streampos> m_chunkEnds;
		std::istream* m_stream;
		u64 m_obfuscationHash = 0;
		std::map<i32, std::string> m_chunkTypeNames;
	};
};