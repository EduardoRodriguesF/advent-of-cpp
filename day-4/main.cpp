#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "split.h"
#include "range.h"
using namespace std;

vector<int> resolve_elf_range(const string& line) {
	auto splitted = split_once(line, '-');

	return range(stoi(splitted.first), stoi(splitted.second));
}

int main() {
	ifstream file("data.txt");

	if (!file.is_open()) {
		throw runtime_error("Failed to open file");
	}

	string line;
	int duplicate_count = 0, overlap_count = 0;
	while (getline(file, line)) {
		auto group = split_once(line, ',');

		vector<int> pivot = resolve_elf_range(group.first);
		vector<int> other = resolve_elf_range(group.second);

		if (pivot.size() > other.size()) swap(pivot, other); // The smallest range is used as pivot

		if (pivot.front() >= other.front() && pivot.back() <= other.back()) {
			duplicate_count++;
		}

		for (const int& item : pivot) {
			if (count(other.begin(), other.end(), item) > 0) {
				overlap_count++;
				break;
			}
		}
	}

	cout << "Duplicate: " << duplicate_count << endl;
	cout << "Overlaps: " << overlap_count << endl;

	return 0;
}
