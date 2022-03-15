#pragma once
#include "StreamReader.h"
namespace plasma {
	class Engine;
	class PLXStreamReader : public StreamReader {
	public:
		PLXStreamReader(Engine* engine, std::ifstream* stream); // still more arguments to add
		private:
	};
};