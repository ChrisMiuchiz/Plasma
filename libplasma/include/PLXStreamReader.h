#pragma once
#include "ChunkStreamReader.h"
#include <vector>
#include <map>
#include <string>
#include "types.h"
namespace plasma {
	class Engine;
	struct PageInfo;
	class Node;
	class Texture;
	class PLXStreamReader : public ChunkStreamReader {
	public:
		PLXStreamReader(Engine* engine, PageInfo* pageInfo, Node* targetNode, u32 fileFlags, std::ifstream* stream, std::vector<u64> keys);
		void Read();
		std::string ParseChunkHeader();
		bool Decompress(const std::vector<u8>& input, std::vector<u8>& output);
		void ReadPlasmaGraphics();
		bool ReadSeal();
		void ReadTexture();

		enum class FLAGS : u32 {
			CHECK_FORMAT = 0x40
		};

	private:
		std::vector<u64> m_keys;
		u32 m_fileFlags = 0;
		Node* m_targetNode;
		Engine* m_engine;
		PageInfo* m_pageInfo;

		std::map<i32, Texture*> m_textures;
	};
};