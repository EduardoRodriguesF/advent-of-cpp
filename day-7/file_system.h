#pragma once

#include <memory>
#include <string>
#include <map>
#include <utility>
#include <vector>

struct File {
	std::string name;
	int size;
};

struct Dir {
	std::string name;
	std::map<std::string, std::shared_ptr<File>> files;
	std::map<std::string, std::shared_ptr<Dir>> dirs;

	// Sum of file sizes directly stored in this `Dir`
	int files_size() const;

	// Recursive `Dir` size
	int size() const;
};

class FileSystem {
public:
	FileSystem() : home_dir(std::make_shared<Dir>(Dir { "/" })) {};

	std::shared_ptr<Dir> home() const; 
	std::shared_ptr<Dir> dir(std::vector<std::string> path) const;

	void insert_file(std::vector<std::string> path, File file);
	void insert_dir(std::vector<std::string> path, Dir dir);

	void print() const;

private:
	std::shared_ptr<Dir> home_dir;
};
