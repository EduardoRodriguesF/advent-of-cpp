#include "grid.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

size_t total_visible_trees(const Grid &map) {
	size_t result = 0;
	auto [x_size, y_size] = map.sizes();

	for (size_t x = 0; x < x_size; x++) {
		for (size_t y = 0; y < y_size; y++) {
			auto cell = map.at(x, y).value();
			auto direct_neighbors = cell->direct_neighbors_list();

			bool is_sorrounded = std::all_of(direct_neighbors.begin(), direct_neighbors.end(), [](std::optional<GridCell *> cell) {
				return cell.has_value();
			});

			if (!is_sorrounded) {
				result++;
				continue;
			}

			auto adjacents = cell->adjacent_neighbors();

			for (const auto &neighbors : adjacents) {
				bool is_visible = std::all_of(neighbors.begin(), neighbors.end(), [cell](GridCell *neighbor) {
					return neighbor->height < cell->height;
				});

				if (is_visible) {
					result++;
					goto cnt;
				}
			}

			cnt:;
		}
	}

	return result;
}

int main() {
	std::ifstream file("data.txt");
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file");
	}

	std::unique_ptr<Grid> map = std::make_unique<Grid>(file);

	std::cout << total_visible_trees(*map) << std::endl;

	return 0;
}
