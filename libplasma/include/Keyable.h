#pragma once
#include "NamedObject.h"

namespace plasma {
	class Keyable : public NamedObject {
	public:
		Keyable(Engine* engine, const std::wstring& name);
		virtual ~Keyable();
	};
};