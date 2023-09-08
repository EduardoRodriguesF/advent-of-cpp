#include "split.h"

pair<string, string> split_once(const string &str, const char &separator) {
	pair<string, string> result;

	for (int i = 0; i <= str.size(); i++) {
		if (str[i] == separator) {
			result.first = str.substr(0, i);
			result.second = str.substr(i + 1);

			return result;
		}
	}

	// Did not find separator
	result.first = str;

	return result;
}

