#include "Attribute.h"

namespace plasma {
	Attribute::Attribute(const std::string& name) {
		m_name = name;
	}

	Attribute::~Attribute() {
		
	}

	u32 Attribute::CurrentFrame() {
		return m_currentIndex;
	}
};