#pragma once
#include "NamedObject.h"
#include <vector>
#include "types.h"

namespace plasma {
	class Engine;
	class Texture : NamedObject {
	public:
		class Format {
		public:
			u32 BytesPerPixel() const;
			i32 pixelFormat = 1;;
			i32 minFilter = 1;
			i32 maxFilter = 1;
			i32 horizontalWrap = 1;
			i32 verticalWrap = 1;
		};

		Texture(Engine* engine, const std::wstring& name, bool noEngineTexture = false);
		virtual ~Texture();
		void SetPixels(u32 width, u32 height, u8* pixelData, const Format& format);

	private:
		std::vector<u8> m_pixels;
		Format m_format;
		u32 m_width = 0;
		u32 m_height = 0;
		i32 m_textureID = -1;
		bool m_noEngineTexture;

	};
};