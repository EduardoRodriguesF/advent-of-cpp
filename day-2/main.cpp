#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>

class Choice {
public:
	virtual std::string name() const = 0;
	virtual int points() const = 0;
	virtual bool beats(Choice& other) const = 0;
};

class Rock : public Choice {
public:
	std::string name() const override { return "Rock"; };
	int points() const override { return 1; };

	bool beats(Choice& other) const override {
		return other.name() == "Scissor";
	};
};

class Paper : public Choice {
public:
	std::string name() const override { return "Paper"; }
	int points() const override { return 2; }

	bool beats(Choice& other) const override {
		return other.name() == "Rock";
	}
};

class Scissor : public Choice {
public:
	std::string name() const override { return "Scissor"; };
	int points() const override { return 3; };

	bool beats(Choice& other) const override {
		return other.name() == "Paper";
	};
};

enum class Outcome {
	Draw,
	Lose,
	Win,
};

std::ostream& operator<<(std::ostream& os, const Outcome& outcome) {
	switch (outcome) {
		case Outcome::Win: os << "Win"; break;
		case Outcome::Lose: os << "Lose"; break;
		case Outcome::Draw: os << "Draw"; break;
	}

	return os;
}

std::map<char, Choice*> choices = {
	{ 'A', new Rock() },
	{ 'B', new Paper() },
	{ 'C', new Scissor() },
};

std::map<char, Outcome> outcomes = {
	{ 'X', Outcome::Lose },
	{ 'Y', Outcome::Draw },
	{ 'Z', Outcome::Win },
};

Choice* from_outcome(Choice* against, Outcome expected) {
	if (expected == Outcome::Draw) {
		return against;
	};

	Choice* result;
	bool expect = expected == Outcome::Win; // result of beats() should match this bool
	for (const auto &[key, value] : choices) {
		if (against != value && value->beats(*against) == expect) {
			result = value;
			break;
		}
	}

	std::cout << "Expecting " << expected << " against " << against->name() << " = " << result->name() << std::endl;

	return result;
};

int main() {
	std::ifstream file("data.txt");
	int result {0};

	std::string line;
	while (std::getline(file, line)) {
		Choice* opponent = choices[line.at(0)];
		Outcome expected_outcome = outcomes[line.back()];

		Choice* you = from_outcome(opponent, expected_outcome);

		result += you->points();

		if (you->beats(*opponent)) {
			result += 6;
		} else if (opponent->name() == you->name()) {
			result += 3;
		}
	}

	std::cout << "Final score: " << result << std::endl;
} 
