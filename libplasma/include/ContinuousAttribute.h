#pragma once

#include "Attribute.h"
#include <vector>

namespace plasma {
	template <typename T>
	class ContinuousAttribute : Attribute {
	public:
		ContinuousAttribute(const std::string& name, const T& element)
	private:
		std::vector<T> m_frames;
	};
};