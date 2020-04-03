#pragma once
#include "File.h"
class Ico :
	public File
{
public:
	std::string magic1 = "00000100"; //ico
	std::string magic2 = "00000200"; //cur
	std::string magic = ""; //�������� ������������� � ���������� ������ ������ checkFormat() ������ IDSmodule
	int magic_offset = 0; //�������� ���������
	int magic_offset_size; //����� ���������, ������������� � ������������
	std::string format = "ico"; //��� �������, ����������� lower case
	std::string type = "grafics"; //��� ���� �����. ������� � ������ ������
	int filesInside = 0; //���������� ������ (������) ������ �����

	int getFilesInside(std::string fileInBytes);
	std::string getMagic(); //����� ���������� ����� ���������� ����. ����� ��� ������ checkFormat()
	std::string getFormat(); //����� ���������� ������. � ������ ������:gif
	int getMagicOffset(); //����� ���������� �������� �� ���������. ������������ �������� substr() � �������� ������� ���������
	int getMagicOffsetSize(); //����� ���������� �������� �� ���������. ������������ �������� substr() � �������� ������� ���������
	void parseFile(std::string fileInBytes, File* file); //����� ����������� �������� ����� ���������� ������ file


	Ico();
	~Ico();
};

