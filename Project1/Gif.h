/*
������ ����� ������ ���� � ������, � ������� �������
������������ ������ Gif. ������ ������ ����� ��� ��������
������ ���������� ����: GIF87a � GIF89a.

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
	std::string magic=""; //�������� ������������� � ���������� ������ ������ checkFormat() ������ IDSmodule
	int magic_offset = 0; //�������� ���������
	int magic_offset_size; //����� ���������, ������������� � ������������
	std::string format = "gif"; //��� �������, ����������� lower case
	std::string type = "grafics"; //��� ���� �����. ������� � ������ ������

	std::string getMagic(); //����� ���������� ����� ���������� ����. ����� ��� ������ checkFormat()
	std::string getFormat(); //����� ���������� ������. � ������ ������:gif
	int getMagicOffset(); //����� ���������� �������� �� ���������. ������������ �������� substr() � �������� ������� ���������
	int getMagicOffsetSize(); //����� ���������� �������� �� ���������. ������������ �������� substr() � �������� ������� ���������
	void parseFile(std::string fileInBytes, File* file); //����� ����������� �������� ����� ���������� ������ file


	Gif();
	~Gif();
};

