#include "split.h"

std::vector<std::string> split(const std::string &str, const char &separator) {
	std::vector<std::string> result;
	std::string entry;

	for (int i = 0; i < str.size(); i++) {
		char c = str[i];

		if (c == separator) {
			result.push_back(entry);
			entry = "";
			continue;
		}

		entry += c;
	}

	if (!entry.empty()) {
		result.push_back(entry);
	}

	return result;
}
