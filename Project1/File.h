#pragma once
#include <string>

class File
{
public:

	std::string name;			// ��� �����
	std::string magic;			// ����� ���������� ����/���������
	std::string chsum;			// ������������ ����� ���������/�����
	std::string os;				// ������� ��
	std::string time_stamp;		// ������� ������� (����� ��������/����� �����������)
	std::string format;			// ������ �����
	std::string type;			// ��� �����
	std::string compression;	// �����/�������� ������
	std::string extension;		// ���������� �����
	std::string arch;			// ����������� ������� �������
	int network;				// ������� ������� ������������� (0 - ����, 1 - ���)
	int filesInside;			// ���������� ������ ������ (��������� ��� �������)
	unsigned long long size;	// ������ �����
	int magic_offset;			// �������� �� ���������
	int magic_offset_size;		// ����� ���������

	
	File();																// ������ �����������. ����� ��� �������� ������� File* formatObjects[]
	File(std::string format, std::string magic);						// �����������.��������� ��������: ������ �����, ����� ���������� ���� �����
																		 
	int formatToInt();													// {
	int compressionToInt();												// ������ ��� �������� �������� 
	int typeToInt();													// ��� ����� ������� ������ � ��
	int osToInt();														// }

	void getNameAndExt(std::string filePath);							// �����, ������������ ��� � ���������� �����. ���������� �������� � ���� file.name, file.extension
	void getInfo();														// ����� ��� ������ �������� ����� ���������� file

	std::string convertTime(std::string unixTime);						// ����� ������������ ����� ������� ubixTime � ������� ������: ����:������:������� �����:�����:���
	std::string convertBigEndian(std::string bigEndian, int bytes);		// ����� �������� ������� ���� little Endian � big Endian. �������� ���� ��� 2 ���� ���� ��� 4
	std::string convertHexToDec(std::string hexInString);				// ����� ��������� �� 16 �� � 10 ��

	virtual void parseFile(std::string fileInBytes, File* file);		// ����� �������� �� ������� �����. ������ ����������� ����� �������������� ������ �����
	virtual std::string getFormat();									// ����� ���������� ������ �����
	virtual std::string getMagic();										// ����� ���������� ��������� �����
	virtual int getMagicOffset();										// ����� ���������� �������� �� ���������
	virtual int getMagicOffsetSize();									// ����� ���������� ����� ���������

};
