#include "file.h"

#include <utility>

FileObject::FileObject(std::string  pathToFile): pathToFile(std::move(pathToFile)) {}

std::string FileObject::read() {
	if (pathToFile.empty()) {
		throw FileException("file path is empty");
	}
	std::string ret;
	std::string line;
	std::fstream file(pathToFile);

	if (file.is_open()) {
		while (file >> line) {
			ret += line + '\n';
		}
		file.close();
	} else {
		file.close();
		throw FileException("File cannot be opened");
	}
	return ret;
}

void FileObject::save(const std::string& text) {
	if (pathToFile.empty()) {
		throw FileException("file path is empty");
	}
	std::ofstream file(pathToFile);

	if (file.is_open()) {
		file << text;
		file.close();
	} else {
		file.close();
		throw FileException("file cannot be opened");
	}
}

std::string FileObject::getName() {
	if (pathToFile.find('\\') != std::string::npos) {
		return pathToFile.substr(pathToFile.find_last_of('\\') + 1, std::string::npos);
	} else if (pathToFile.find('/') != std::string::npos) {
		return pathToFile.substr(pathToFile.find_last_of('/') + 1, std::string::npos);
	} else {
		return pathToFile;
	}
}