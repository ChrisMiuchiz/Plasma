#include "Shape.h"

namespace plasma {
	Shape::Shape(Engine* engine, const std::wstring& name) : Keyable(engine, name) {
		// TODO: Add shape to engine's shape list
	}
	
	Shape::~Shape() {
		
	}
};