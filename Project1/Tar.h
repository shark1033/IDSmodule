#pragma once
#include "File.h"


//time and other file's parameters have strange representation in hex dump, so yet this class can only define whether the current file is tar or not
class Tar :
	public File
{
public:
	std::string magic = "504b0304";

	std::string magic1 = "7573746172003030";
	std::string magic2 = "7573746172202000";
	std::string format = "tar";
	std::string type = "archive";
	int magic_offset = 257;
	int magic_offset_size;
	int number_of_files_inside = 0;

	Tar();
	std::string getMagic();
	std::string getMagic(int var);
	std::string getFormat();
	int getMagicOffset();
	int getMagicOffsetSize();
	void parseFile(std::string fileInBytes, File* file);

	int getFilesInside(std::string fileInBytes);
};

