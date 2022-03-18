#include "Texture.h"

namespace plasma {
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

};
