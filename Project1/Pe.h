#pragma once
#include "File.h"
#include <vector>
class Pe :
	public File
{

public:
	std::string magic = "4d5a";
	std::string magic2 = "504500"; //this field is required for second check of the file's format
	std::string format = "pe";
	std::string arch_bit;
	std::string directories;


	struct IMAGE_DATA_DIRECTORY {
		long virtualAddress;
		long size;
	};

	std::vector<IMAGE_DATA_DIRECTORY> idd;

	int magic_offset_size;
	int magic_offset = 0;
	int pe_offset; //should be extractes from fileInBytes;
	int section_aligment;
	int image_base;
	int number_of_sections;
	int size_of_optional_header;
	
	
	std::string getTime(std::string fileInBytes);
	std::string getArch(std::string fileInBytes);
	std::string getType(std::string fileInBytes);
	std::string getChsum(std::string fileInBytes);

	void getArchBit(std::string fileInBytes);
	void getIDD(std::string fileInBytes);
	void getSectAlig(std::string fileInBytes);
	void getImageBase(std::string fileInBytes);
	void getSizeOfOh(std::string fileInBytes);
	;

	std::string getMagic();
	std::string getFormat();

	void parseFile(std::string fileInBytes, File* file);
	int getPeHeader(std::string fileInBytes);

	int getMagicOffset();
	int getMagicOffsetSize();
	int getNumbOfSec(std::string fileInBytes);

	bool hasNetwork();
	bool isDriver(std::string fileInBytes);
	bool isCOM();
	bool isNet();





	




	Pe();
	~Pe();

};

