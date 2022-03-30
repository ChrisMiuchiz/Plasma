#pragma once
#include "types.h"

namespace plasma {
	template <u32 N, typename T>
	class Vector {
	public:
		Vector(const T (&elements)[N]) {
			for (u32 i = 0; i < N; i++) {
				m_elements[i] = elements[i];
			}
		}

		T Get(u32 i) {
			T result;
			if (i < N) {
				result = m_elements[i];
			}
			return result;
		}

		void Set(u32 i, T x) {
			if (i < N) {
				m_elements[i] = x;
			}
		}

	private:
		T m_elements[N];
	};
};