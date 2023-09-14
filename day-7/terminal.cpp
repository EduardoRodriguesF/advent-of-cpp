#include "terminal.h"

std::vector<std::string> Terminal::pwd() const {
	return this->working_dir;
}

void Terminal::cd(std::string path) {
	if (path == "..") {
		if (!this->working_dir.empty()) {
			this->working_dir.pop_back();
		}

		return;
	}

	if (path == "/") {
		return this->working_dir.clear();
	}

	this->working_dir.push_back(path);
}
