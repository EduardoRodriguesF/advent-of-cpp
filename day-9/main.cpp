#include "coords.h"
#include "rope.h"
#include "split.h"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <thread>

void draw(const Rope &rope, const std::set<std::pair<int, int>> trail) {
	system("clear");
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 150; x++) {
			Pos pos(x, y);

			if (pos == rope.get_head()) {
				std::cout << 'H';
			} else if (pos == rope.get_tail()) {
				std::cout << 'T';
			} else if (trail.find(static_cast<std::pair<int, int>>(pos)) != trail.end()) {
				std::cout << '#';
			} else {
				std::cout << '.';
			}
		}

		std::cout << "\n";
	}

	std::cout << std::endl;
}

int main() {
	Rope rope(25, 12);
	std::set<std::pair<int, int>> trail;

	draw(rope, trail);

	std::ifstream file("data.txt");
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file");
	}

	std::string line;
	while (std::getline(file, line)) {
		auto [dir_key, repetitions_str] = split_once(line, ' ');
		Direction direction {};
		int repetitions = std::stoi(repetitions_str);

		switch (dir_key[0]) {
			case 'U':
				direction = Direction::Up;
				break;
			case 'R':
				direction = Direction::Right;
				break;
			case 'D':
				direction = Direction::Down;
				break;
			case 'L':
				direction = Direction::Left;
				break;
			default:
				std::cerr << "Invalid direction " << dir_key[0] << std::endl;
				exit(1);
		}

		while (repetitions > 0) {
			repetitions--;
			rope.move(direction);
			trail.insert(static_cast<std::pair<int, int>>(rope.get_tail()));

			std::this_thread::sleep_for(std::chrono::milliseconds());
		}
	}

	draw(rope, trail);
	std::cout << trail.size() << std::endl;

	return 0;
}
