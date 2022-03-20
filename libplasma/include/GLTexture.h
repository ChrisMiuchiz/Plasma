#pragma once
#include "Texture.h"

namespace plasma {
	class GLTexture : public Texture {
	public:
		GLTexture(Engine* engine, u32 width, u32 height, u8* pixelData,
			const Format& format, const std::wstring& name, bool noEngineTexture);
		virtual ~GLTexture();
	private:
	};
};