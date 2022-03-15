#pragma once
namespace plasma {
	class Engine;
	class Object {
	public:
		Object(plasma::Engine* engine);
		virtual ~Object();
		plasma::Engine* GetEngine();
	private:
		plasma::Engine* m_engine;
	};
};