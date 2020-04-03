#include "Ico.h"
#include <iostream>

std::string Ico::getMagic() {
	return this->magic;
}

std::string Ico::getFormat() {
	return this->format;
}
int Ico::getMagicOffset() {
	return this->magic_offset;
}
int Ico::getMagicOffsetSize() {
	return this->magic_offset_size;
}

Ico::Ico() {
	this->magic_offset_size = this->magic1.length();
}
Ico::~Ico() {}

void Ico::parseFile(std::string fileInBytes, File* file) {
	file->format = this->format;
	file->type = this->type;
	file->filesInside = this->getFilesInside(fileInBytes);
}

int Ico::getFilesInside(std::string fileInBytes) {
	std::string s = fileInBytes.substr(9, 1);
	std::cout << std::stoi(s);
	return std::stoi(s);
}
