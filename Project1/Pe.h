#pragma once
#include "File.h"
class Pe :
	public File
{
	std::string magic = "4d5a";
	int pe_offset; //should be extractes from fileInBytes;
	std::string cpu_type;
	std::string magic2 = "504500"; //this field is required for second check of the file's format
	std::string format = "pe";
	std::string type;
	int magic_offset = 0;
	int magic_offset_size;

	std::string getTime(std::string fileInBytes);


};

