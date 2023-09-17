#include "grid.h"
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

Grid::Grid(std::ifstream &file) {
	std::string line;

	size_t y = 0;
	while (std::getline(file, line)) {
		std::vector<std::unique_ptr<GridCell>> row;
		std::istringstream ss(line);
		char tree;

		size_t x = 0;
		while (ss >> tree) {
			auto cell = GridCell(*this);

			cell.pos = Pos { x, y };
			cell.height = tree - '0'; // converted to int

			row.push_back(std::make_unique<GridCell>(cell));
			x++;
		}

		this->data.push_back(std::move(row));
		y++;
	}
}

std::optional<GridCell *> Grid::at(size_t x, size_t y) const {
	if (y >= this->data.size() || x >= this->data[y].size()) {
		return std::nullopt;
	}

	return this->data[y][x].get();
}

CellNeighbors GridCell::direct_neighbors() const {
	CellNeighbors result;

	if (this->pos.y > 0) {
		result.top = this->parent.at(pos.x, pos.y - 1);
	}

	if (this->pos.x > 0) {
		result.left = this->parent.at(pos.x - 1, pos.y);
	}

	result.bottom = this->parent.at(pos.x, pos.y + 1);
	result.right = this->parent.at(pos.x + 1, pos.y);

	return result;
}

std::vector<std::optional<GridCell *>> GridCell::direct_neighbors_list() const {
	auto neighbors = this->direct_neighbors();

	return {
		neighbors.top,
		neighbors.right,
		neighbors.bottom,
		neighbors.left
	};
}

std::vector<std::vector<GridCell *>> GridCell::adjacent_neighbors() const {
	std::vector<std::vector<GridCell *>> result(4);

	for (size_t ny = this->pos.y - 1; ny >= 0; ny--) {
		auto node = this->parent.at(this->pos.x, ny);
		if (!node.has_value()) {
			break;
		}

		result[Direction::Top].push_back(node.value());
	}

	for (size_t nx = this->pos.x + 1; nx < this->parent.sizes().first; nx++) {
		auto node = this->parent.at(nx, this->pos.y);
		if (!node.has_value()) {
			break;
		}

		result[Direction::Right].push_back(node.value());
	}

	for (size_t ny = this->pos.y + 1; ny < this->parent.sizes().second; ny++) {
		auto node = this->parent.at(this->pos.x, ny);
		if (!node.has_value()) {
			break;
		}

		result[Direction::Bottom].push_back(node.value());
	}

	for (size_t nx = this->pos.x - 1; nx >= 0; nx--) {
		auto node = this->parent.at(nx, this->pos.y);
		if (!node.has_value()) {
			break;
		}

		result[Direction::Left].push_back(node.value());
	}

	return result;
}

size_t GridCell::scenetic_score() const {
	auto directions = this->adjacent_neighbors();
	std::vector<size_t> scores(directions.size());

	std::transform(directions.begin(), directions.end(), scores.begin(), [this](std::vector<GridCell *> neighbors) {
		size_t score = 0;

		for (const auto &neighbor : neighbors) {
			score++;

			if (neighbor->height >= this->height) {
				break;
			}
		}

		return score;
	});

	return std::accumulate(scores.begin(), scores.end(), 1, std::multiplies<size_t>{});
}

std::pair<size_t, size_t> Grid::sizes() const {
	if (this->data.empty()) {
		return std::make_pair(0, 0);
	}

	size_t x_size = this->data[0].size();
	size_t y_size = this->data.size();

	return std::make_pair(x_size, y_size);
}
