#pragma once

#include "Attribute.h"
#include <vector>

namespace plasma {
	template <typename T>
	class ContinuousAttribute : public Attribute {
	public:
		using AttributeType = T;
		ContinuousAttribute(const std::string& name, const T& element) : Attribute(name) {
			m_frames.assign(2, element);
		}

		virtual ~ContinuousAttribute() {
		
		}

		T* Back() {
			return m_frames.back();
		}
	private:
		std::vector<T> m_frames;
	};
};