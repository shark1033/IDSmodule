#pragma once
#include "File.h"
class Elf :
	public File
{
public:

	
	std::string magic = "7f454c46";	// ����� ���������� ����/���������	
	std::string format = "elf";
	std::string arch_bit;

	std::string net_array[10] = { "socket" , "connect", "accept",   //may be here we can add popular network libs
								 "listen", "sendto", "recvfrom",
								 "select", "poll", "epoll" };

									
	
	int magic_offset = 0;	// �������� �� ���������
	int magic_offset_size;	// ����� ���������
	

	bool isBigEndian;

	

	long long str_tab_section_offset; //�������� �� ������ �����
	long str_tab_section_size; //������ ������ �����


	int str_tab_section_index; //������ ������ ����� #3
	long long str_tab_structure_offset; //�������� �� ������ ����� 

	long long sh_str_tab_offset; //�������� �� ���������, ����������� ������ shstrtab (�� elf header) #1
	long long sht_offset; //�������� �� ������� ������ (section header table), ������� �������� ���������, ���������� ���� � �������   (�� elf header) #1
	long long sh_str_ndx; //������ ������ shstrtab (�� elf header)
	long long sh_num; //���������� �������� � section header table (�� elf header)
	long long sh_ent_size; //������ �������� � section header table (�� elf header)

	long long sh_str_tab_section_offset; //�������� �� ������ section header string table, ������� �������� ����� ������.   #2
	int sh_str_tab_section_size; // ������ ������ section header string table  #2
	


    void parseFile(std::string fileInBytes, File* file);


	std::string getMagic();
	std::string getFormat();
	std::string getArch(std::string fileInBytes);
	std::string getType(std::string fileInBytes);
	std::string getChsum(std::string fileInBytes);
	std::string getOs(std::string fileInBytes);

	void getArchBit(std::string fileInBytes);
    void getByteOrder(std::string fileInBytes);
	void getHeaderInfo(std::string fileInBytes);
	void getStrabOffset();
	void getStrTabIndex(std::string fileInBytes);
	void getShStrTabOffsetAndSize(std::string fileInBytes);
	void getStrTabSectionOffsetAndSize(std::string fileInBytes);
	void defineNetworkMode(std::string fileInBytes);
	void isCoreFile(std::string sub);
	

	int getMagicOffset();
	int getMagicOffsetSize();

	
	bool isEqualed(std::string sub);

	
    Elf();
};

