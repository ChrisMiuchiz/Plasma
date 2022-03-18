#pragma once
#include "Object.h"
#include <string>
namespace plasma {
	class Engine;
	class NamedObject : public Object {
	public:
		NamedObject(Engine* engine, const std::wstring& name);
		virtual ~NamedObject();
	private:
		std::wstring m_name;

	};

};