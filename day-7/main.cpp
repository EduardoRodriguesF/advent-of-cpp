#include "file_system.h"
#include "terminal.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

int main() {
	std::ifstream file("data.txt");
	FileSystem fs;
	Terminal terminal;

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file");
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		std::string word;

		ss >> word;
		if (word == "$") {
			ss >> word;

			if (word == "cd") {
				ss >> word;
				terminal.cd(word);
				continue;
			} else if (word == "ls") {
				continue;
			} else {
				throw std::runtime_error("Not implemented");
			}
		}

		if (word == "dir") {
			ss >> word;
			fs.insert_dir(terminal.pwd(), Dir { word });
			continue;
		} 

		try {
			std::string name;
			int size = std::stoi(word);

			ss >> name;

			fs.insert_file(terminal.pwd(), File { name, size });
			continue;
		} catch (...) {
			throw std::runtime_error("Failed to interpret line");
		}
	}

	std::cout << fs.home()->size() << std::endl;
}
