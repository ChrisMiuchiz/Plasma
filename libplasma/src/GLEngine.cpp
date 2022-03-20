#include "GLEngine.h"
#include "GLTexture.h"

namespace plasma {
	GLEngine::GLEngine() {
	
	}

	GLEngine::~GLEngine() {
	
	}

	Texture* GLEngine::NewTexture(u32 width, u32 height, u8* pixelData,
		const Texture::Format& format, const std::wstring& name,
		bool noEngineTexture) {
		return new GLTexture(this, width, height, pixelData, format, name, noEngineTexture);
	}
};