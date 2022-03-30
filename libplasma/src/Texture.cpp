#include "Texture.h"

namespace plasma {
	u32 Texture::Format::BytesPerPixel() const {
		return this->pixelFormat ? 4 : 3;
	}

	Texture::Texture(Engine* engine, const std::wstring& name, bool noEngineTexture) :
		NamedObject(engine, name)
	{
		m_noEngineTexture = noEngineTexture;

		//TODO: add texture to engine's texture list

		if (!m_noEngineTexture) {
			// TODO: add this to engine's texture... map?
		}
	}
	
	Texture::~Texture() {
	
	}

	void Texture::SetPixels(u32 width, u32 height, u8* pixelData, const Format& format) {
		// This is just asking for an OOB read...
		m_width = width;
		m_height = height;
		u32 bytesPerPixel = format.BytesPerPixel();
		m_pixels.resize(m_width * m_height * bytesPerPixel);
		memcpy(m_pixels.data(), pixelData, m_pixels.size());
	}

};
