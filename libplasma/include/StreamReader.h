#pragma once
#include <fstream>
#include "types.h"

namespace plasma {
	class StreamReader {
	public:
		StreamReader(std::ifstream* stream);

		i32 ReadI32();
		f32 ReadF32();

	private:
		std::istream* m_stream;

	};
};