#pragma once
#include "File.h"

//Данный класс описывает поля формата файла Uboot или uImage. Кроме выделенных полей заголовок содержит много полезной информации, такой, как тип файла внутри uImage, его контр. сумма и тд.
//Данная информация будет использована в других версиях библиотеки.


class Uboot :
	public File
{
public:
	Uboot();

	std::string magic = "27051956";
	int magic_offset = 0;
	int magic_offset_size;
	std::string format = "uimage";
	std::string type = "image";


	void parseFile(std::string fileInBytes, File* file);


	std::string getMagic();
	std::string getFormat();
	int getMagicOffset();
	int getMagicOffsetSize();

	std::string getOS(std::string fileInBytes);
	std::string getChsum(std::string fileInBytes);
	std::string getCompression(std::string fileInBytes);
	std::string getTime(std::string fileInBytes);
	std::string getType();
	std::string getArch(std::string fileInBytes);

};

