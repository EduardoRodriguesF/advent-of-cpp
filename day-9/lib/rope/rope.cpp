#include "rope.h"
#include <math.h>

Rope::Rope(size_t length) {
	for (size_t i = 0; i < length; i++) {
		this->knots.push_back(Pos(0, 0));
	}
}

Pos Rope::head() const { return this->knots.front(); }
Pos Rope::tail() const { return this->knots.back(); }
std::vector<Pos> Rope::get_knots() const { return this->knots; }

void Rope::move(Direction direction) {
	Pos delta(direction);
	Pos lead = this->head() + delta;

	size_t i = 0;
	for (Pos &pos : this->knots) {
		std::swap(lead, pos);

		if (i < this->knots.size()) {
			auto next = this->knots[i + 1];

			Pos distance = pos - next;
			if (abs(distance.x) > 1 || abs(distance.y) > 1) {
				i++;
				continue;
			}
		}

		break; // No need to move nothing else
	}
}
