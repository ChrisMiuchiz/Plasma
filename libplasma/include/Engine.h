#pragma once
#include "PageInfo.h"
#include "types.h"
#include <fstream>
#include <vector>
#include "Texture.h"

namespace plasma {
	class Node;
	class Engine {
	public:
		Engine();
		virtual ~Engine();

		void ReadPLXFile(PageInfo* pageInfo, Node* targetNode, u32 fileFlags, std::ifstream* stream, std::vector<u64> keys);
		virtual Texture* NewTexture(u32 width, u32 height, u8* pixelData,
			const Texture::Format& format, const std::wstring& name,
			bool noEngineTexture) = 0;
	private:
		PageInfo m_pageInfo;
	};
};