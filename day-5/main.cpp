#include "split.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

class CrateMover {
protected:
	std::stack<char>* from;
	std::stack<char>* to;

public:
	CrateMover(std::stack<char>* from_ptr, std::stack<char>* to_ptr) {
		this->from = from_ptr;
		this->to = to_ptr;
	}

	virtual void move(int count) {
		while (count > 0 && !from->empty()) {
			this->to->push(this->from->top());

			count--;
			this->from->pop();
		}
	}
};

class CrateMover9001 : public CrateMover {
public:
	using CrateMover::CrateMover;

	void move(int count) override {
		std::stack<char> aux;

		while (count > 0 && !from->empty()) {
			aux.push(this->from->top());

			count--;
			this->from->pop();
		}

		while (!aux.empty()) {
			this->to->push(aux.top());
			aux.pop();
		}
	}
};

int main() {
	std::vector<std::stack<char>> supplies(9);

	std::ifstream file("data.txt");

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file");
	}

	std::string line;
	std::stack<std::string> initial_supplies;
	// Organizes stack
	while (getline(file, line)) {
		if (empty(line)) {
			initial_supplies.pop(); // skips numbers row
			break;
		}

		initial_supplies.push(line);
	}


	std::string supply_line;
	while (!initial_supplies.empty()) {
		supply_line = initial_supplies.top();

		int supply_index = -1;
		for (int i = 1; i <= supply_line.size(); i += 4) {
			supply_index++;
			char pkg = supply_line[i];

			if (pkg == ' ') {
				continue;
			}

			supplies[supply_index].push(pkg);
		}

		initial_supplies.pop();
	};

	// Follow instructions
	while (getline(file, line)) {
		std::vector<std::string> words = split(line, ' ');

		int from = stoi(words[3]) - 1; // Count starts at 1
		int to = stoi(words[5]) - 1;

		auto crate_mover = std::make_unique<CrateMover9001>(&supplies[from], &supplies[to]);
		int move_count = stoi(words[1]);

		crate_mover->move(move_count);
	}


	for (auto st : supplies) {
		std::cout << st.top();
	}
	std::cout << std::endl;

	return 0;
}
