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
	class TextShape;
	class PLXStreamReader : public ChunkStreamReader {
	public:
		PLXStreamReader(Engine* engine, PageInfo* pageInfo, Node* targetNode, u32 fileFlags, std::ifstream* stream, std::vector<u64> keys);
		void Read();
		std::string ParseChunkHeader();
		bool Decompress(const std::vector<u8>& input, std::vector<u8>& output);
		void ReadPlasmaGraphics();
		bool ReadSeal();
		void ReadTexture();
		TextShape* ReadTextShape();

	private:
		template <typename T>
		void RawAttributeDataRead(T* target) {
			m_stream->read(target, sizeof(T));
		}

		template <>
		void RawAttributeDataRead<std::wstring>(std::wstring* target) {
			std::wstring str = ReadWString();
			target->assign(str);
		}

	public:
		// Example: ReadAttribute<ContinuousAttribute<Vector<4, float>>()
		template <typename T>
		void ReadAttribute(T& attribute) {
			EnterChunk();

			u32 attribtueFrameCount = 0;

			if (FinishChunk()) return;

			do {
				std::string chunkName = ParseChunkHeader();

				if (chunkName == "Attribute.frame") {
					EnterChunk();

					if (attribtueFrameCount == attribute.Size()) {
						attribute.DuplicateElement();
					}

					//m_stream->read(attribute.Back(), sizeof(T::AttributeType));
					RawAttributeDataRead(attribute.Back());

					FinishChunk();
				}
				else if (chunkName == "Attribute.sequence") {
					// TODO
				}
				else {
					SkipChunk();
				}
			} while (!FinishChunk());

		}

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