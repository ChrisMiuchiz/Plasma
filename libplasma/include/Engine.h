#pragma once
#include "PageInfo.h"
#include "types.h"
#include <fstream>
#include <vector>
namespace plasma {
	class Node;
	class Engine {
	public:
		Engine();
		virtual ~Engine();

		void ReadPLXFile(PageInfo* pageInfo, Node* targetNode, u32 fileFlags, std::ifstream* stream, std::vector<u64> keys);
	private:
		PageInfo m_pageInfo;
	};
};