#include "NamedObject.h"

namespace plasma {
	NamedObject::NamedObject(Engine* engine, const std::wstring& name) :
		Object(engine)
	{
		m_name = name;
	}

	NamedObject::~NamedObject() {
	
	}
};