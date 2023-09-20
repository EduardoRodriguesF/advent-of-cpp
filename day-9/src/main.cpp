#include "coords/coords.h"
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
#include <map>

const int LENGTH = 10;

void draw(const Rope &rope, const std::set<std::pair<int, int>> trail) {
	std::map<std::pair<int, int>, char> rope_draw_area;

	int i = 0;
	for (auto &knot : rope.get_knots()) {
		char r = std::to_string(i)[0];
		if (i == 0) {
			r = 'H';
		} else if (i == rope.get_knots().size() - 1) {
			r = 'T';
		}

		rope_draw_area.insert({ static_cast<std::pair<int, int>>(knot), r });

		i++;
	}

	system("clear");
	for (int y = -25; y < 25; y++) {
		for (int x = -50; x < 50; x++) {
			Pos pos(x, y);

			auto c = rope_draw_area.find(static_cast<std::pair<int, int>>(pos));
			if (c != rope_draw_area.end()) {
				std::cout << c->second;
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
	Rope rope(LENGTH);
	std::set<std::pair<int, int>> trail;

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
			trail.insert(static_cast<std::pair<int, int>>(rope.tail()));

			draw(rope, trail);
			std::this_thread::sleep_for(std::chrono::milliseconds());
		}
	}

	std::cout << trail.size() << std::endl;

	return 0;
}
