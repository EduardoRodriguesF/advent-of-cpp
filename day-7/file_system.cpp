#include "file_system.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>

std::shared_ptr<Dir> FileSystem::home() const {
	return this->home_dir;
}

std::shared_ptr<Dir> FileSystem::dir(std::vector<std::string> path) const {
	auto dir = this->home();

	for (const auto &glob : path) {
		dir = dir->dirs.find(glob)->second;
	}

	return dir;
}

void FileSystem::insert_file(std::vector<std::string> path, File file) {
	auto dir = this->dir(path);

	dir->files.insert_or_assign(file.name, std::make_shared<File>(file));
}

void FileSystem::insert_dir(std::vector<std::string> path, Dir directory) {
	auto dir = this->dir(path);

	if (dir == nullptr) {
		std::cerr << "No path directory found at " << path.back() << std::endl;
		exit(1);
	}

	dir->dirs.insert_or_assign(directory.name, std::make_shared<Dir>(directory));
}

void print_recursive_dir(size_t lvl, Dir dir) {
	for (const auto &[path, file] : dir.files) {
		for (size_t i = 0; i < lvl; i++) {
			std::cout << "  ";
		} 
		std::cout << path << " (" << file->size << ")" << std::endl;
	}

	for (const auto &[path, d] : dir.dirs) {
		for (size_t i = 0; i < lvl; i++) {
			std::cout << "  ";
		} 
		std::cout << path << std::endl;

		print_recursive_dir(lvl + 1, *d);
	}
}

void FileSystem::print() const {
	print_recursive_dir(0, *this->home());
}
