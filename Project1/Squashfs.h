#pragma once
#include "File.h"
class Squashfs :
	public File
{
public:
	std::string magic = "68737173";
	std::string format = "squashfs";
	std::string type = "archive";
	int magic_offset = 0;
	int magic_offset_size;
	int number_of_files_inside = 0;

	Squashfs();
	std::string getMagic();
	std::string getFormat();
	std::string getCompression(std::string fileInBytes);
	std::string getTime(std::string fileInbytes);
	int getMagicOffset();
	int getMagicOffsetSize();
	void parseFile(std::string fileInBytes, File* file);
	int getFilesInside(std::string fileInBytes);
};


