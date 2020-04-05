#include "Gif.h"

std::string Gif::getMagic() {
	return this->magic;
}

std::string Gif::getFormat() {
	return this->format;
}
int Gif::getMagicOffset() {
	return this->magic_offset;
	}
int Gif::getMagicOffsetSize() {
	return this->magic_offset_size;
}

Gif::Gif() {
	this->magic_offset_size = this->magic1.length();
}
Gif::~Gif(){}

void Gif::parseFile(std::string fileInBytes, File* file) {
	file->format = this->format;
	file->type = this->type;
}

