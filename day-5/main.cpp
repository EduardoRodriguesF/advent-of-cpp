#include "split.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

class Action {
private:
	stack<char>* from;
	stack<char>* to;

public:
	Action(stack<char>* from_ptr, stack<char>* to_ptr) {
		this->from = from_ptr;
		this->to = to_ptr;
	}

	void move(int count) {
		while (count > 0 && !from->empty()) {
			to->push(from->top());

			count--;
			from->pop();
		}
	}
};

int main() {
	vector<stack<char>> supplies(9);

	ifstream file("data.txt");

	if (!file.is_open()) {
		throw runtime_error("Failed to open file");
	}

	string line;
	stack<string> initial_supplies;
	// Organizes stack
	while (getline(file, line)) {
		if (empty(line)) {
			initial_supplies.pop(); // skips numbers row
			break;
		}

		initial_supplies.push(line);
	}


	string supply_line;
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
		vector<string> words = split(line, ' ');

		int from = stoi(words[3]) - 1; // Count starts at 1
		int to = stoi(words[5]) - 1;

		auto action = make_unique<Action>(&supplies[from], &supplies[to]);
		int move_count = stoi(words[1]);

		action->move(move_count);
	}


	for (auto st : supplies) {
		cout << st.top();
	}
	cout << endl;

	return 0;
}
