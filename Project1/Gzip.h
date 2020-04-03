#pragma once
#include "File.h"
#include <string>
#include <map>
class Gzip :
	public File
{	
public:
	Gzip();

	std::string magic="1f8b";
	int magic_offset = 0;
	int magic_offset_size;
	std::string format="gzip";
	std::string type = "archive";

	
	void parseFile(std::string fileInBytes, File* file);


	std::string getMagic();
	std::string getFormat();
	int getMagicOffset();
	int getMagicOffsetSize();
	long double getSize(std::string);
	std::string getOS(std::string fileInBytes);
	std::string getChsum(std::string fileInBytes);
	std::string getCompesion(std::string fileInBytes);
	std::string getTime(std::string fileInBytes);
	std::string getType();

};

