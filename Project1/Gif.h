/*
Данный класс хранит поля и методы, с помощью которых
определяется формат Gif. Данный формат имеет два варианта
набора магических байт: GIF87a и GIF89a.

*/

#pragma once
#include "File.h"
#include <string>
class Gif :
	public File
{
public:

	std::string magic1 = "474946383761"; //GIF87a
	std::string magic2 = "474946383961"; //GIF89a
	std::string magic=""; //Значение присваивается в результате работы метода checkFormat() класса IDSmodule
	int magic_offset = 0; //Смещение сигнатуры
	int magic_offset_size; //Длина сигнатуры, инициализация в конструкторе
	std::string format = "gif"; //Имя формата, обязательно lower case
	std::string type = "grafics"; //Имя типа файла. графика в данном случае

	std::string getMagic(); //Метод возвращает набор магических байт. Нужен для работы checkFormat()
	std::string getFormat(); //Метод возвращает формат. В данном случае:gif
	int getMagicOffset(); //Метод возвращает смещение до сигнатуры. Используется функцией substr() в качестве первого параметра
	int getMagicOffsetSize(); //Метод возвращает смещение до сигнатуры. Используется функцией substr() в качестве второго параметра
	void parseFile(std::string fileInBytes, File* file); //Метод присваивает значения полям экземпляра класса file


	Gif();
	~Gif();
};

