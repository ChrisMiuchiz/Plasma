#pragma once
#include "NamedObject.h"
#include <vector>
#include "types.h"

namespace plasma {
	class Engine;
	class Texture : NamedObject {
	public:
		struct Format {
			i32 pixelFormat;
			i32 minFilter;
			i32 maxFilter;
			i32 horizontalWrap;
			i32 verticalWrap;
		};

		Texture(Engine* engine, const std::wstring& name, bool noEngineTexture = false);
		virtual ~Texture();
		void SetPixels(u32 width, u32 height, u8* pixelData, const Format& format);

	private:
		std::vector<u8> m_pixels;
		Format m_format = {1,1,1,1,1};
		u32 m_width = 0;
		u32 m_height = 0;
		i32 m_textureID = -1;
		bool m_noEngineTexture;

	};
};