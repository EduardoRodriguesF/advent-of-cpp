#include "coords.h"
#include <utility>

Pos operator+(Pos lfs, Pos rhs) {
	int x = lfs.x + rhs.x;
	int y = lfs.y + rhs.y;

	return Pos(x, y);
}

Pos operator-(Pos lfs, Pos rhs) {
	int x = lfs.x - rhs.x;
	int y = lfs.y - rhs.y;

	return Pos(x, y);
}

Pos& Pos::operator+=(Pos rhs) {
	this->x += rhs.x;
	this->y += rhs.y;

	return *this;
}

Pos& Pos::operator-=(Pos rhs) {
	this->x -= rhs.x;
	this->y -= rhs.y;

	return *this;
}

bool operator==(Pos lfs, Pos rhs) {
	return lfs.x == rhs.x && lfs.y == rhs.y;
}

Pos::Pos(const Direction &direction) : x(0), y(0) {
	switch (direction) {
		case Direction::Up:
			this->y = -1;
			break;
		case Direction::Right:
			this->x = 1;
			break;
		case Direction::Down:
			this->y = 1;
			break;
		case Direction::Left:
			this->x = -1;
			break;
	}
}

 Pos::operator std::pair<int, int>() {
	return std::make_pair(this->x, this->y);
}
