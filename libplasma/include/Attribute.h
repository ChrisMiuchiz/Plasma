#pragma once
#include <string>
#include "types.h"

namespace plasma {
	class Attribute {
	public:
		Attribute(const std::string& name);
		virtual ~Attribute();
		virtual u32 Size() = 0;
		//Another virtual function missing
		virtual void CopyToCurrent(u32 sourceFrame) = 0;
		virtual void RemoveElement(u32 frame) = 0;
		virtual void CopyFromCurrent(u32 targetFrame) = 0;
		//Another virtual function missing
	private:
		std::string m_name;
	};

};