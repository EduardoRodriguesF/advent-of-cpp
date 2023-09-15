#include "grid.h"
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

Grid::Grid(std::ifstream &file) {
	std::string line;

	while (std::getline(file, line)) {
		std::vector<int> row;
		std::istringstream ss(line);
		char tree;

		while (ss >> tree) {
			row.push_back(tree - '0'); // converted to int
		}

		this->data.push_back(row);
	}
}

std::optional<GridCell> Grid::at(size_t x, size_t y) const {
	return this->at(Pos { x, y });
}

std::optional<GridCell> Grid::at(Pos pos) const {
	if (pos.y > this->data.size() - 1 || pos.x > this->data[pos.y].size()) {
		return std::nullopt;
	}

	GridCell cell;

	cell.parent = std::make_shared<Grid>(*this);
	cell.pos = pos;
	cell.height = this->data[pos.y][pos.x];

	return cell;
}

CellNeighbors GridCell::direct_neighbors() const {
	CellNeighbors result;

	if (this->pos.y > 0) {
		result.top = this->parent->at(pos.x, pos.y - 1);
	}

	if (this->pos.x > 0) {
		result.left = this->parent->at(pos.x - 1, pos.y);
	}

	result.bottom = this->parent->at(pos.x, pos.y + 1);
	result.right = this->parent->at(pos.x + 1, pos.y);

	return result;
}

std::vector<std::optional<GridCell>> GridCell::direct_neighbors_list() const {
	auto neighbors = this->direct_neighbors();

	return {
		neighbors.top,
		neighbors.right,
		neighbors.bottom,
		neighbors.left
	};
}

std::vector<std::vector<GridCell>> GridCell::adjacent_neighbors() const {
	std::vector<std::vector<GridCell>> result(4);

	for (size_t ny = this->pos.y - 1; ny >= 0; ny--) {
		auto node = this->parent->at(this->pos.x, ny);
		if (!node.has_value()) {
			break;
		}

		result[Direction::Top].push_back(node.value());
	}

	for (size_t nx = this->pos.x + 1; nx < this->parent->sizes().first; nx++) {
		auto node = this->parent->at(nx, this->pos.y);
		if (!node.has_value()) {
			break;
		}

		result[Direction::Right].push_back(node.value());
	}

	for (size_t ny = this->pos.y + 1; ny < this->parent->sizes().second; ny++) {
		auto node = this->parent->at(this->pos.x, ny);
		if (!node.has_value()) {
			break;
		}

		result[Direction::Bottom].push_back(node.value());
	}

	for (size_t nx = this->pos.x - 1; nx >= 0; nx--) {
		auto node = this->parent->at(nx, this->pos.y);
		if (!node.has_value()) {
			break;
		}

		result[Direction::Left].push_back(node.value());
	}

	return result;
}

std::pair<size_t, size_t> Grid::sizes() const {
	if (this->data.empty()) {
		return std::make_pair(0, 0);
	}

	size_t x_size = this->data[0].size();
	size_t y_size = this->data.size();

	return std::make_pair(x_size, y_size);
}
