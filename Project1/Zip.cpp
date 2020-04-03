#include "Zip.h"
#include <iostream>

//Zip::Zip(): File("504b0304", "zip") {}
Zip::Zip(){
	this->magic_offset_size = this->magic.length();
}
std::string Zip::getFormat() {
		return this->format;
}
std::string Zip::getMagic() {
	return this->magic;
}
int Zip::getMagicOffset() {
	return this->magic_offset;
}
int Zip::getMagicOffsetSize(){
	return this->magic_offset_size;
}
int Zip::getFilesInside(std::string fileInBytes) {
	std::string s, sub1, sub2;
	sub1= fileInBytes.substr(20, 2);
	sub2 = fileInBytes.substr(22, 2);
	s = sub2 + sub1;
	char tab2[1024];
	strncpy_s(tab2, s.c_str(), sizeof(tab2));
	tab2[sizeof(tab2) - 1] = 0;
	int i, result, k, p;
	result = 0;
	p = strlen(tab2) - 1;
	for (i = 0; tab2[i] != '\0'; i++)
	{
		switch (toupper(tab2[i]))
		{
		case 'A': k = 10; break;
		case 'B': k = 11; break;
		case 'C': k = 12; break;
		case 'D': k = 13; break;
		case 'E': k = 14; break;
		case 'F': k = 15; break;
		case '1': k = 1; break;
		case '2': k = 2; break;
		case '3': k = 3; break;
		case '4': k = 4; break;
		case '5': k = 5; break;
		case '6': k = 6; break;
		case '7': k = 7; break;
		case '8': k = 8; break;
		case '9': k = 9; break;
		case '0': k = 0; break;
		}
		result = result + k * pow(16, p); //формула перевода из 16 СС в 10 СС
		p--;
	}
	return result;
}

void Zip::parseFile(std::string fileInBytes, File* file) {
	file->type = type;
	file->filesInside = this->getFilesInside(fileInBytes);

	
}

int Zip::findEOCDR(std::string fileInBytes) {

	if (fileInBytes.find("504b0506") == std::string::npos) {
		return 0;
	}
	else {
		return fileInBytes.find("504b0506");
	}
}