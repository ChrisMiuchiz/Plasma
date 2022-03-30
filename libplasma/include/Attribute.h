#pragma once
#include <string>
#include "types.h"

namespace plasma {
	class Attribute {
	public:
		Attribute(const std::string& name);
		u32 CurrentFrame();
		virtual ~Attribute();
		virtual u32 Size() = 0;
		virtual u32 DuplicateElement() = 0;
		virtual void CopyToCurrent(u32 sourceFrame) = 0;
		virtual void RemoveElement(u32 frame) = 0;
		virtual void CopyFromCurrent(u32 targetFrame) = 0;
		//Another virtual function missing
	private:
		u32 m_currentIndex = 0;
		std::string m_name;
	};

};