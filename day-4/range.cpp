#include "range.h"

vector<int> range(const int start, const int end) {
	vector<int> result;

	for (int i = start; i <= end; i++) {
		result.push_back(i);
	}

	return result;
}
