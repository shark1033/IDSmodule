#pragma once
#include "File.h"
class Undefined :
	public File
{
public:
	std::string format = "undefined";
	std::string magic = "no magic";

	void parseFile(std::string fileInBytes, File* file);
};

