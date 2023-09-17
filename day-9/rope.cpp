#include "rope.h"
#include <math.h>

Pos Rope::get_head() const { return this->head; }
Pos Rope::get_tail() const { return this->tail; }

void Rope::move(Direction direction) {
	Pos delta(direction);
	Pos dest = this->head + delta;

	Pos tail_distance = dest - this->tail;

	if (abs(tail_distance.x) > 1 || abs(tail_distance.y) > 1) {
		this->tail = this->head;
	}

	this->head = dest;
}
