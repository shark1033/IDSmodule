#pragma once
#include "File.h"
class Elf :
	public File
{
public:

	
	std::string magic = "7f454c46";	// набор магических байт/сигнатруа	
	std::string format = "elf";
	std::string arch_bit;

	std::string net_array[10] = { "socket" , "connect", "accept",   //may be here we can add popular network libs
								 "listen", "sendto", "recvfrom",
								 "select", "poll", "epoll" };

									
	
	int magic_offset = 0;	// смещение до сигнатуры
	int magic_offset_size;	// длина сигнатуры
	

	bool isBigEndian;

	

	long long str_tab_section_offset; //смещение до секции строк
	long str_tab_section_size; //размер секции строк


	int str_tab_section_index; //индекс секции строк #3
	long long str_tab_structure_offset; //смещение до табоиц строк 

	long long sh_str_tab_offset; //смещение до структуры, описывающей секцию shstrtab (из elf header) #1
	long long sht_offset; //смещение до таблицы секций (section header table), которая содержит структуры, содержащие инфу о секциях   (из elf header) #1
	long long sh_str_ndx; //инедкс секции shstrtab (из elf header)
	long long sh_num; //колчисетво структур в section header table (из elf header)
	long long sh_ent_size; //размер структур в section header table (из elf header)

	long long sh_str_tab_section_offset; //смещение до секции section header string table, которая содержит имена секций.   #2
	int sh_str_tab_section_size; // размер секции section header string table  #2
	


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

