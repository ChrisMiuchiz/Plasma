#pragma once
#include "Keyable.h"

namespace plasma {
	class Shape : public Keyable {
	public:
		Shape(Engine* engine, const std::wstring& name);
		virtual ~Shape();
		// This has many more virtual functions, and this is an abstract class
	};
};