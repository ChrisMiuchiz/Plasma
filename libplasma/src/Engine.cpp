#include "Engine.h"
#include "PLXStreamReader.h"
#include "TextShape.h"

namespace plasma {
	Engine::Engine() {
		m_pageInfo.pageWidth = 1000.0;
		m_pageInfo.pageHeight = 1000.0;
		m_pageInfo.unit = 0;
		m_pageInfo.dpi = 72.0;
		m_pageInfo.pageColor[0] = 1.0;
		m_pageInfo.pageColor[1] = 1.0;
		m_pageInfo.pageColor[2] = 1.0;
		m_pageInfo.pageColor[3] = 1.0;
	}

	Engine::~Engine() {
	
	}

	void Engine::ReadPLXFile(PageInfo* pageInfo, Node* targetNode, u32 fileFlags, std::ifstream* stream, std::vector<u64> keys) {
		if (!pageInfo) {
			pageInfo = &m_pageInfo;
		}

		PLXStreamReader reader(this, pageInfo, targetNode, fileFlags, stream, keys);
		reader.Read();
	}

	TextShape* Engine::NewTextShape(const std::wstring& text, const std::wstring& name) {
		return new TextShape(this, name, text);
	}
};