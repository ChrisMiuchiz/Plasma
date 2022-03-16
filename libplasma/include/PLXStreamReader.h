#pragma once
#include "StreamReader.h"
#include <vector>
#include <map>
#include <string>
#include "types.h"
namespace plasma {
	class Engine;
	struct PageInfo;
	class Node;
	class PLXStreamReader : public StreamReader {
	public:
		PLXStreamReader(Engine* engine, PageInfo* pageInfo, Node* targetNode, u32 fileFlags, std::ifstream* stream, std::vector<u64> keys);
		void Read();
		std::string ParseChunkHeader();

		enum class FLAGS : u32 {
			CHECK_FORMAT = 0x40
		};

	private:
		std::vector<u64> m_keys;
		u32 m_fileFlags = 0;
		Node* m_targetNode;
		Engine* m_engine;
		PageInfo* m_pageInfo;
	};
};