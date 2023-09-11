#include "split.h"

vector<string> split(const string &str, const char &separator) {
	vector<string> result;
	string entry;

	for (int i = 0; i <= str.size(); i++) {
		char c = str[i];

		if (c == separator || i == str.size()) {
			result.push_back(entry);
			entry = "";
			continue;
		}

		entry += c;
	}

	return result;
}
