#pragma once
#include "File.h"
class Ico :
	public File
{
public:
	std::string magic1 = "00000100"; //ico
	std::string magic2 = "00000200"; //cur
	std::string magic = ""; //«начение присваиваетс¤ в результате работы метода checkFormat() класса IDSmodule
	int magic_offset = 0; //—мещение сигнатуры
	int magic_offset_size; //ƒлина сигнатуры, инициализаци¤ в конструкторе
	std::string format = "ico"; //»м¤ формата, об¤зательно lower case
	std::string type = "grafics"; //»м¤ типа файла. графика в данном случае
	int filesInside = 0; //количество файлов (иконок) внутри файла

	int getFilesInside(std::string fileInBytes);
	std::string getMagic(); //ћетод возвращает набор магических байт. Ќужен дл¤ работы checkFormat()
	std::string getFormat(); //ћетод возвращает формат. ¬ данном случае:gif
	int getMagicOffset(); //ћетод возвращает смещение до сигнатуры. »спользуетс¤ функцией substr() в качестве первого параметра
	int getMagicOffsetSize(); //ћетод возвращает смещение до сигнатуры. »спользуетс¤ функцией substr() в качестве второго параметра
	void parseFile(std::string fileInBytes, File* file); //ћетод присваивает значени¤ пол¤м экземпл¤ра класса file


	Ico();
	~Ico();
};

