#pragma once
#include <fstream>
#include "types.h"
#include <map>

namespace plasma {
	class StreamReader {
	public:
		friend class PLXStreamReader;
		StreamReader(std::ifstream* stream);

		i32 ReadI32();
		f32 ReadF32();

	private:
		std::istream* m_stream;
		u64 m_obfuscationHash = 0;
		std::map<i32, std::string> m_chunkTypeNames;
	};
};