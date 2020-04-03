#pragma once
#include "File.h"
class Ico :
	public File
{
public:
	std::string magic1 = "00000100"; //ico
	std::string magic2 = "00000200"; //cur
	std::string magic = ""; //Значение присваивается в результате работы метода checkFormat() класса IDSmodule
	int magic_offset = 0; //Смещение сигнатуры
	int magic_offset_size; //Длина сигнатуры, инициализация в конструкторе
	std::string format = "ico"; //Имя формата, обязательно lower case
	std::string type = "grafics"; //Имя типа файла. графика в данном случае
	int filesInside = 0; //количество файлов (иконок) внутри файла

	int getFilesInside(std::string fileInBytes);
	std::string getMagic(); //Метод возвращает набор магических байт. Нужен для работы checkFormat()
	std::string getFormat(); //Метод возвращает формат. В данном случае:gif
	int getMagicOffset(); //Метод возвращает смещение до сигнатуры. Используется функцией substr() в качестве первого параметра
	int getMagicOffsetSize(); //Метод возвращает смещение до сигнатуры. Используется функцией substr() в качестве второго параметра
	void parseFile(std::string fileInBytes, File* file); //Метод присваивает значения полям экземпляра класса file


	Ico();
	~Ico();
};

