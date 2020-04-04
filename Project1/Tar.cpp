#include "Tar.h"


Tar::Tar() {
	this->magic_offset_size = this->magic1.length();
}

std::string Tar::getMagic() {
	return this->magic;
}

std::string Tar::getMagic(int var) {
	if (var == 1) {
		return this->magic1;
	}
	else {
		return this->magic2;
	}
}

std::string Tar::getFormat() {
	return this->format;
}

int Tar::getMagicOffset() {
	return this->magic_offset;
}

int Tar::getMagicOffsetSize() {
	return this->magic_offset_size;
}

void Tar::parseFile(std::string fileInBytes, File* file) {
	file->type = this->type;

}

//how to count files insede without reading the whole file? maybe check each 512 byte in order to find tar file headers?
int Tar::getFilesInside(std::string fileInBytes) {
	return 0;
}