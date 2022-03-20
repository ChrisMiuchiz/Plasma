#include "plutils.h"

namespace plasma {
	std::wstring StringToWstring(const std::string& input) {
		std::wstring result;

		for (char letter : input) {
			result.push_back(letter);
		}

		return result;
	}
};