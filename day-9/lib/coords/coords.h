#pragma once

#include <utility>
enum class Direction {
	Up,
	Right,
	Down,
	Left,
};

struct Pos {
	int x;
	int y;

	Pos(int x, int y) : x(x), y(y) {};
	Pos(const Direction& direction);

	Pos& operator+=(Pos rhs);
	Pos& operator-=(Pos rhs);

	explicit operator std::pair<int, int>();
};

Pos operator+(Pos lfs, Pos rhs);
Pos operator-(Pos lfs, Pos rhs);
bool operator==(Pos lfs, Pos rhs);
