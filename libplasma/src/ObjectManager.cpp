#include "ObjectManager.h"
namespace plasma {
	ObjectManager::ObjectManager() {
		
	}

	ObjectManager::~ObjectManager() {
		for (Object* object : m_objects) {
			delete object;
		}
	}
};