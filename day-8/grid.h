#include <fstream>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class Grid;

struct CellNeighbors;

enum Direction {
	Top,
	Right,
	Bottom,
	Left
};

struct Pos {
	size_t x;
	size_t y;
};

struct GridCell {
	std::shared_ptr<Grid> parent;
	unsigned int height;
	Pos pos;

	CellNeighbors direct_neighbors() const;
	std::vector<std::optional<GridCell>> direct_neighbors_list() const;

	std::vector<std::vector<GridCell>> adjacent_neighbors() const;
};

struct CellNeighbors {
	std::optional<GridCell> top;
	std::optional<GridCell> right;
	std::optional<GridCell> bottom;
	std::optional<GridCell> left;
};

class Grid {
public:
	Grid(std::ifstream &file);

	std::vector<int> neighbors() const;
	std::optional<GridCell> at(Pos pos) const;
	std::optional<GridCell> at(size_t x, size_t y) const;

	std::pair<size_t, size_t> sizes() const;

private:
	std::vector<std::vector<int>> data;
};
