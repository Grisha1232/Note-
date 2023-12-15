#include "errorFile.h"

#include <utility>
#include <string>
#include <fstream>

class FileObject {
public:
	FileObject() {
		pathToFile = "";
	}

	explicit FileObject(std::string pathToFile);

	std::string read();
	void save(const std::string& text);
	std::string getName();
private:
	std::string pathToFile;
};