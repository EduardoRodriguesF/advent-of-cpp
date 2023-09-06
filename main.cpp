#include <_ctype.h>
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <list>
#include <numeric>
#include <set>
#include <string>
#include <tuple>
#include <vector>

const int NUM = 31;

class Item {
public:
	char letter;

	Item(char item) : letter(item) {}

	int priority() const {
		int offset {};

		if (isupper(letter)) {
			offset = 26;
		}

		return (letter & NUM) + offset;
	}

	bool operator==(const Item& rhs) const {
		return this->letter == rhs.letter;
	}
};

class Rucksack {
public:
	std::vector<Item> items;

	Rucksack(std::string items) {
		for (const char letter : items) {
			auto item = new Item(letter);
			this->items.push_back(*item);
		}
	}

	std::tuple<std::vector<Item>, std::vector<Item>> compartments() const {
		int half_len = this->items.size() / 2;

		std::vector<Item> first_compartment(this->items.begin(), this->items.end() - half_len);
		std::vector<Item> second_compartment(this->items.begin() + half_len, this->items.end());

		return std::make_tuple(first_compartment, second_compartment);
	}
};

int main() {
	std::ifstream file("data.txt");

	int total_priority {};
	std::vector<Rucksack> rucksacks;

	std::string line;
	while (std::getline(file, line)) {
		std::set<int> similars;
		Rucksack* rucksack = new Rucksack(line);

		std::vector<Item> first;
		std::vector<Item> second;
		std::tie(first, second) = rucksack->compartments();

		for (const auto first_item : first) {
			for (const auto second_item : second) {
				if (first_item == second_item) {
					similars.insert(first_item.priority());
				}
			}
		}

		total_priority += std::reduce(similars.begin(), similars.end(), 0, [](int acc, int priority) {
			return acc + priority;
		});

		rucksacks.push_back(*rucksack);
	}

	std::cout << "Total joined priority: " << total_priority << std::endl;
}
