#include "Object.h"

namespace plasma {
	Object::Object(plasma::Engine* engine) {
		this->m_engine = engine;
		// TODO: Add self to Engine
	};

	Object::~Object() {
		// TODO: Remove self from Engine
	}

	plasma::Engine* Object::GetEngine() {
		return m_engine;
	}
};