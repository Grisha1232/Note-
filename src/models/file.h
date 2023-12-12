#include <fstream>
#include <string>
#include "errorFile.h"

class FileObject {
public:
	FileObject() {
		pathToFile = "";
	}
	explicit FileObject(std::string  pathToFile);

	std::string read();
	void save(const std::string& text);
	std::string getName();
private:
	std::string pathToFile;
};