#include "file_system.h"
#include "terminal.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

int total_dir_size(const FileSystem &fs, int max_size) {
	int result = 0;
	std::vector<std::shared_ptr<Dir>> candidates { fs.home() };
	std::vector<std::shared_ptr<Dir>> next_candidates;

	while (!candidates.empty()) {
		for (const auto &dir : candidates) {
			int size = dir->size();

			if (size <= max_size) {
				result += size;
				continue;
			}

			for (const auto &[_, next_dir] : dir->dirs) {
				next_candidates.push_back(next_dir);
			}
		}

		candidates.swap(next_candidates);
		next_candidates.clear();
	}

	return result;
}

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

	std::cout << total_dir_size(fs, 100000) << std::endl;
}
