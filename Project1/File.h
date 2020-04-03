#pragma once
#include <string>
class File
{
public:

	//std::string filePath;

	std::string name;
	std::string magic;
	std::string chsum;
	std::string owner;
	std::string os;
	std::string date_changed;
	std::string date_created;
	std::string format;
	std::string type;
	std::string compression;
	std::string version;
	std::string extension;
	std::string arch;
	int network;
	int filesInside;
	unsigned long long compressed_size; //compressed
	unsigned long long uncompressed_size; //uncompressed
	int magic_offset;
	int magic_offset_size;

	
	//File(std::string magic, std::string format);
	File();
	File(std::string format, std::string magic);

	int formatToInt();
	int compressionToInt();
	int typeToInt();
	int osToInt();

	void getNameAndExt(std::string filePath);
	void getInfo();
	std::string convertTime(std::string unixTime);
	std::string convertBigEndian(std::string bigEndian, int bytes);
	std::string convertHexToDec(std::string hexInString);

	virtual void parseFile(std::string fileInBytes, File* file);
	virtual std::string getFormat() {
		return this->format;
	}
	virtual std::string getMagic() {
		return this->magic;
	}
	virtual int getMagicOffset() {
		return this->magic_offset;
	}
	virtual int getMagicOffsetSize() {
		return this->magic_offset_size;
	}

};
