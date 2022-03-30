#include "TextShape.h"

namespace plasma {
	TextShape::TextShape(Engine* engine, const std::wstring& name, const std::wstring& text) : 
		Shape(engine, name),
		m_string("string", text)
	{
		
	}

	TextShape::~TextShape() {
	
	}
};