#pragma once
#include "File.h"
#include <string>
class Zip :
	public File
{
public:
	std::string magic = "504b0304";
	std::string format = "zip";
	std::string type = "archive";
	int magic_offset=0;
	int magic_offset_size;
	int number_of_files_inside=0;

	Zip();
	std::string getMagic();
	std::string getFormat();
	int getMagicOffset();
	int getMagicOffsetSize();
	void parseFile(std::string fileInBytes, File* file);
	int findEOCDR(std::string fileInBytes);
	int getFilesInside(std::string fileInBytes);
};

