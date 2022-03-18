#pragma once
#include "NamedObject.h"
#include <vector>
#include "types.h"

namespace plasma {
	class Engine;
	class Texture : NamedObject {
	public:
		Texture(Engine* engine, const std::wstring& name, bool noEngineTexture = false);
		virtual ~Texture();
	private:
		struct Format {
			int pixelFormat;
			int minFilter;
			int maxFilter;
			int horizontalWrap;
			int verticalWrap;
		};
		std::vector<u8> m_pixels;
		Format m_format = {1,1,1,1,1};
		int m_width = 0;
		int m_height = 0;
		int m_textureID = -1;
		bool m_noEngineTexture;

	};
};