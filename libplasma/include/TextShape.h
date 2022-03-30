#pragma once
#include "Shape.h"
#include "DiscreteAttribute.h"
#include "ContinuousAttribute.h"

namespace plasma {
	class TextShape : public Shape {
	public:
		TextShape(Engine* engine, const std::wstring& name, const std::wstring& text);
		virtual ~TextShape();
	private:
		DiscreteAttribute<std::wstring> m_string;

	};
};