#include "StreamReader.h"

namespace plasma {
	StreamReader::StreamReader(std::ifstream* stream) {
		m_stream = stream;
	}

	i32 StreamReader::ReadI32() {
		i32 result = 0;
		m_stream->read((char*)&result, sizeof(result));
		return result;
	}


	f32 StreamReader::ReadF32() {
		f32 result = 0;
		m_stream->read((char*)&result, sizeof(result));
		return result;
	}
};