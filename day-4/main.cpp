#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <utility>
#include "split.h"
#include "range.h"
using namespace std;

list<int> resolve_elf_range(const string& line) {
	auto splitted = split_once(line, '-');
	pair<int, int> sections = make_pair(stoi(splitted.first), stoi(splitted.second));

	return range(sections.first, sections.second);
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

		list<int> pivot = resolve_elf_range(group.first);
		list<int> other = resolve_elf_range(group.second);

		if (pivot.size() > other.size()) swap(pivot, other); // The smallest range is used as pivot

		if (pivot.front() >= other.front() && pivot.back() <= other.back()) {
			duplicate_count++;
		}

		for (const int& item : pivot) {
			if (find(other.begin(), other.end(), item) != other.end()) {
				overlap_count++;
				break;
			}
		}
	}

	cout << "Duplicate: " << duplicate_count << endl;
	cout << "Overlaps: " << overlap_count << endl;

	return 0;
}
