#include "range.h"

list<int> range(const int start, const int end) {
	int size = end - start;
	list<int> result;

	for (int i = start; i <= end; i++) {
		result.push_back(i);
	}

	return result;
}
