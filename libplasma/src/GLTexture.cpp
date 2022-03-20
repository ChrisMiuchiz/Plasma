#include "GLTexture.h"

namespace plasma {
	GLTexture::GLTexture(Engine* engine, u32 width, u32 height, u8* pixelData,
		const Format& format, const std::wstring& name, bool noEngineTexture) :
		Texture(engine, name, noEngineTexture)
	{
		// sets GL texture at 0x60 to 0
		SetPixels(width, height, pixelData, format);
	}

	GLTexture::~GLTexture() {
		//TODO: glDeleteTExtures
	}

};