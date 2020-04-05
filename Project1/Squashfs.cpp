#include "Squashfs.h"
#include <iostream>



Squashfs::Squashfs() {
	this->magic_offset_size = this->magic.length();
}

std::string Squashfs::getMagic(){
	return this->magic;
	}

std::string Squashfs::getFormat() {
	return this->format;
}

int Squashfs::getMagicOffset() {
	return this->magic_offset;
}

int Squashfs::getMagicOffsetSize() {
	return this->magic_offset_size;
}

void Squashfs::parseFile(std::string fileInBytes, File* file) {
	file->compression = this->getCompression(fileInBytes);
	file->time_stamp = this->getTime(fileInBytes);
	file->type = this->type;

}
int Squashfs::getFilesInside(std::string fileInBytes) {
	return this->filesInside;
}

std::string Squashfs::getCompression(std::string fileInBytes) {
	std::string s, sub1, sub2;
	sub1 = fileInBytes.substr(40, 2);
	sub2 = fileInBytes.substr(42, 2);
	s = sub2 + sub1;
	int bytes = std::stoi(s);
	std::cout << bytes;
	switch (bytes)
	{
	case 1: return "gzip";
	case 2: return "lzma";
	case 3: return "lzo";
	case 4: return "xz";
	case 5: return "lz4";
	case 6: return "zstd";
	default:
		return "undefined";
	}
}

std::string Squashfs::getTime(std::string fileInBytes) {
	std::string unixTime = fileInBytes.substr(16, 8);
	unixTime = convertBigEndian(unixTime, 4);
	return convertTime(unixTime);
}