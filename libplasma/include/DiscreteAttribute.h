#pragma once

#include "Attribute.h"
#include <vector>

namespace plasma {
	template <typename T>
	class DiscreteAttribute : public Attribute {
	public:
		using AttributeType = T;
		DiscreteAttribute(const std::string& name, const T& element) : Attribute(name) {
			m_frames.assign(2, element);
		}

		virtual ~DiscreteAttribute() {
		
		}

		T* Back() {
			return &m_frames.back();
		}

		T* Current() {
			return &m_frames[CurrentFrame()];
		}

		virtual u32 Size() {
			return m_frames.size();
		}

		virtual u32 DuplicateElement() {
			T element;
			if (Size() != 0) {
				element = *Back();
			}
			m_frames.push_back(element);
			return Size() - 1;
		}

		virtual void CopyToCurrent(u32 sourceFrame) {
			if (Size() != 0 && sourceFrame < Size()) {
				*Current() = m_frames[sourceFrame];
			}
		}

		virtual void RemoveElement(u32 frame) {
			if (Size() != 0 && frame < Size()) {
				m_frames.erase(m_frames.begin() + frame);
			}
		}

		virtual void CopyFromCurrent(u32 targetFrame) {
			if (Size() != 0 && targetFrame < Size()) {
				m_frames[targetFrame] = *Current();
			}
		}

	private:
		std::vector<T> m_frames;
	};
};