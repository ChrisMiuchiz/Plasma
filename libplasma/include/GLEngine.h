#pragma once
#include "Engine.h"
#include "Texture.h"
#include "types.h"
namespace plasma {
	class GLEngine : public Engine {
	public:
		GLEngine();
		virtual ~GLEngine();
		virtual Texture* NewTexture(u32 width, u32 height, u8* pixelData, 
			const Texture::Format& format, const std::wstring& name, 
			bool noEngineTexture);

	private:

	};
};