#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
	std::ifstream file("data/elves.txt");

	if (!file.is_open()) {
		return 1;
	}

	int i{0};
	std::string line;
	std::vector<int> elves = {0};

	while (std::getline(file, line)) {
		if (line.empty()) {
			i++;
			elves.push_back(0);
			continue;
		}

		try {
			elves.back() += std::stoi(line);
		} catch (const std::exception& e) {
			std::cerr << "Failed to parse line: " << line << std::endl;
			return 1;
		}
	}

	std::sort(elves.begin(), elves.end(), [](int a, int b) { return a > b; });

	int top_elves_sum = 0;
	for (int i = 0; i < std::min(3, static_cast<int>(elves.size())); i++) {
		std::cout << elves[i] << std::endl;
		top_elves_sum += elves[i];
	}

	std::cout << top_elves_sum << std::endl;
}
