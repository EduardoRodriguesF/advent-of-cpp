#include <_ctype.h>
#include <algorithm>
#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <numeric>
#include <optional>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
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

	bool operator!=(const Item& rhs) const {
		return this->letter != rhs.letter;
	}

};

class Rucksack {
public:
	std::vector<std::shared_ptr<Item>> items;

	Rucksack(std::string items) {
		for (const char letter : items) {
			auto item = std::make_unique<Item>(letter);
			this->items.push_back(std::move(item));
		}
	}

	std::pair<std::vector<std::shared_ptr<Item>>, std::vector<std::shared_ptr<Item>>> compartments() const {
		int half_len = this->items.size() / 2;

		std::vector<std::shared_ptr<Item>> first_compartment(this->items.begin(), this->items.end() - half_len);
		std::vector<std::shared_ptr<Item>> second_compartment(this->items.begin() + half_len, this->items.end());

		return std::make_pair(first_compartment, second_compartment);
	}
};

std::optional<Item> find_group_item(Rucksack* a, Rucksack* b, Rucksack* c) {
	std::unordered_set<char> a_types, b_types, c_types;

	for (const auto a_item : a->items) {
		a_types.insert(a_item->letter);
	}
	for (const auto b_item : b->items) {
		b_types.insert(b_item->letter);
	}
	for (const auto c_item : c->items) {
		c_types.insert(c_item->letter);
	}

	for (const char& item : a_types) {
		if (b_types.count(item) > 0 && c_types.count(item) > 0) {
			return Item(item);
		}
	}

	return {};
}

int main() {
	std::ifstream file("data.txt");

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file");
	}

	int total_priority {};
	int total_group_priority {};
	std::vector<Rucksack> rucksacks;

	std::string line;
	while (std::getline(file, line)) {
		std::unordered_set<int> similars;
		auto rucksack = std::make_unique<Rucksack>(line);

		auto compartments = rucksack->compartments();

		for (const auto first_item : compartments.first) {
			for (const auto second_item : compartments.second) {
				if (*first_item == *second_item) {
					similars.insert(first_item->priority());
				}
			}
		}

		total_priority += std::accumulate(similars.begin(), similars.end(), 0);
		rucksacks.push_back(std::move(*rucksack));
	}

	for (int i = 0; i < rucksacks.size() - 2; i += 3) {
		auto maybe_group_item = find_group_item(&rucksacks[i], &rucksacks[i + 1], &rucksacks[i + 2]);

		if (maybe_group_item.has_value()) {
			total_group_priority += maybe_group_item.value().priority();
		}
	}

	std::cout << "Total joined priority: " << total_priority << std::endl;
	std::cout << "Total group priority: " << total_group_priority << std::endl;

	file.close();
}
