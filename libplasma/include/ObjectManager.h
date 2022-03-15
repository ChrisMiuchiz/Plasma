#pragma once
#include <list>
namespace plasma {
	class Object;
	class ObjectManager {
	public:
		ObjectManager();
		virtual ~ObjectManager();
	private:
		std::list<Object*> m_objects;
	};
};