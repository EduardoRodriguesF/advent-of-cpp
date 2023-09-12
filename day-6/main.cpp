#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

const int MARKER_SIZE = 14;

int find_marker_position(std::string str) {
	for (int i = MARKER_SIZE - 1; i < str.length(); i++) {
		std::string marker = str.substr(i - MARKER_SIZE + 1, MARKER_SIZE);
		std::unordered_map<char, int> marker_map;

		bool has_repeated {};
		for (const char &c : marker) {
			if (marker_map[c] > 0) {
				has_repeated = true;
			}

			marker_map[c]++;
		}

		if (!has_repeated) {
			std::cout << marker << "\n";
			return i;
		}
	}

	return -1;
}

int main() {
	std::ifstream file("data.txt");
	std::string line;

	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file");
	}

	std::getline(file, line);

	if (line.length() < MARKER_SIZE) {
		throw std::runtime_error("Data is too small to locate a marker");
	}

	int index = find_marker_position(line);

	std::cout << index + 1 << std::endl;

	return 0;
}
