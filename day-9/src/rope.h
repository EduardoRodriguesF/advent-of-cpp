#pragma once

#include "coords.h"
#include <vector>

class Rope {
public:
	Pos head() const;
	Pos tail() const;
	std::vector<Pos> get_knots() const;

	Rope(size_t length);

	void move(Direction direction);

private:
	std::vector<Pos> knots;
};
