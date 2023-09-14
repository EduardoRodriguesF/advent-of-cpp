#pragma once

#include "file_system.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class Terminal {
public:
	std::vector<std::string> pwd() const;

	void cd(std::string path);

private:
	std::vector<std::string> working_dir;
};
