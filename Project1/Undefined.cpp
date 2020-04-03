#include "Undefined.h"


void Undefined::parseFile(std::string fileInBytes, File* file){
	file->format = this->format;
	file->magic = this->magic;
}