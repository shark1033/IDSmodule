#pragma once
#include "File.h"
class Script :
	public File
{
public:
	std::string name;
	std::string magic = "no_magic";
	std::string os="unix";
	std::string format="script";
	std::string type = "executable";
	std::string extension;

	std::string arr[5] = { "#!/bin", "#!/usr/bin", "#!/bin/sh", "#!/bin/bash", "#!/system/bin/sh" };
	int numb_arr[5] = {6,10,9,11,16};

	void parseFile(std::string fileInBytes, File* file);
	std::string getFormat();

	std::string getName(std::string fileInBytes);
	std::string getMagic();
};

