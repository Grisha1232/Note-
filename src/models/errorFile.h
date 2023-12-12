#include <string>
#include <utility>

class FileException: std::exception {
public:
	FileException(std::string  message): message(std::move(message)) {}

	virtual std::string getMessage() const {
		return message;
	}

private:
	const std::string message;
};

