#include "Script.h"


void Script::parseFile(std::string fileInBytes, File* file) {
	file->format = this->format;
	file->type = this->type;
	file->os = this->os;
}

std::string Script::getFormat() {
	return this->format;
}
std::string Script::getMagic() {
	return this->magic;
}


