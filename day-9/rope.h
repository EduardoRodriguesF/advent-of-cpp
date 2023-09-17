#pragma once

#include "coords.h"

class Rope {
public:
	Pos get_head() const;
	Pos get_tail() const;

	Rope(int x, int y) : head(x, y), tail(x, y) {};

	void move(Direction direction);

private:
	Pos head;
	Pos tail;
};
