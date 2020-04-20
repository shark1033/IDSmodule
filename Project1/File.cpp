#include "File.h"
#include <string>
#include <iostream>
#include <vector>
#include <regex>


std::string File::convertBigEndian(std::string bigEndian, int bytes) {
	if (bytes == 2) {
		std::string sub1, sub2;
		sub1 = bigEndian.substr(0, 2);
		sub2 = bigEndian.substr(2, 2);
		return sub2 + sub1;
	}
	else if (bytes == 4) {
		std::string sub1, sub2, sub3, sub4;
		sub1 = bigEndian.substr(0, 2);
		sub2 = bigEndian.substr(2, 2);
		sub3 = bigEndian.substr(4, 2);
		sub4 = bigEndian.substr(6, 2);
		return sub4 + sub3 + sub2 + sub1;
	}

	else if (bytes == 8) {
		std::string sub1, sub2, sub3, sub4, sub5, sub6, sub7, sub8;
		sub1 = bigEndian.substr(0, 2);
		sub2 = bigEndian.substr(2, 2);
		sub3 = bigEndian.substr(4, 2);
		sub4 = bigEndian.substr(6, 2);
		sub5 = bigEndian.substr(8, 2);
		sub6 = bigEndian.substr(10, 2);
		sub7 = bigEndian.substr(12, 2);
		sub8 = bigEndian.substr(14, 2);
		return sub8 + sub7 + sub6 + sub5 +sub4 + sub3 + sub2 + sub1;
	}

	else {
		std::cout << "WRONG ARGUMENT";
		return 0;
	}
	
}

std::string File::convertTime(std::string unixTime) {
	char tab2[1024];
	strncpy_s(tab2, unixTime.c_str(), sizeof(tab2));
	tab2[sizeof(tab2) - 1] = 0;

	int i, result, k, p;
	result = 0;
	p = strlen(tab2) - 1;
	for (i = 0; tab2[i] != '\0'; i++)
	{
		switch (toupper(tab2[i]))
		{
		case 'A': k = 10; break;
		case 'B': k = 11; break;
		case 'C': k = 12; break;
		case 'D': k = 13; break;
		case 'E': k = 14; break;
		case 'F': k = 15; break;
		case '1': k = 1; break;
		case '2': k = 2; break;
		case '3': k = 3; break;
		case '4': k = 4; break;
		case '5': k = 5; break;
		case '6': k = 6; break;
		case '7': k = 7; break;
		case '8': k = 8; break;
		case '9': k = 9; break;
		case '0': k = 0; break;
		}
		result = result + k * pow(16, p); //формула перевода из 16 СС в 10 СС
		p--;
	}
	//конвертация значения времени из unix формата в обычный 
	std::string years, month, days, hours, minutes, seconds;
	int year, day, hour, minute, second, extra_days, days_minus_leap_days, extra, days_this_year;

	year = result / 31436000 + 1970; //года с 1970 + 1970 = текущий год
	extra_days = (year - 1969) / 4; //доп дни в связи с весокосными годами
	day = result / 86400; //дней после 1970
	days_minus_leap_days = day - extra_days; //минус весокосные дни
	days_this_year = days_minus_leap_days % 365; // дней в этом году

	//структура описывает месяца
	struct Month
	{
		std::string name;
		int days;
	};

	std::vector<Month> months{
		{ "Jan", 31 }, { "Feb", 28 }, { "Mar", 31 }, { "Apr", 30 }, { "May", 31 }, { "Jun", 30 },
		{ "Jul", 31 }, { "Aug", 31 }, { "Sep", 30 }, { "Oct", 31 }, { "Nov", 30 }, { "Dec", 31 } };

	//проверка на високосный год
	bool leaf_year = false;
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
		leaf_year = true;
		months.at(1).days = 29;  //если високосный, то +1 к дням в феврале
		days_this_year++;		//нужно прибавить, иначе неправильный день
	}

	for (const auto& it : months) {

		if (days_this_year == 0) {
			days_this_year = it.days;  //если при вычитании получили 0=>день равен числу дней в месяце
			month = it.name;
			break;
		}
		if (days_this_year < it.days) {
			month = it.name;
			break;
		}
		days_this_year -= it.days;

	}
	//часы, минуты, секунды
	second = result - (day * 86400); //секунды в общем
	hour = second / 3600; //часы
	extra = (second - (hour * 3600));
	minute = extra / 60;//минуты
	second = extra - (minute * 60);//секунды
	
	std::string time = checkTimeFormat(hour) + ":" + checkTimeFormat(minute) + ":" + checkTimeFormat(second) + " " + checkTimeFormat(days_this_year) + "/" + month + "/" + std::to_string(year);
	return time;
}


std::string File::convertBytesToAscii(std::string sub) {
	std::string ascii_string;

	for (int i = 0; i < sub.length()-1; i += 2) {
		
		ascii_string.push_back((char)std::stoi(convertHexToDec(sub.substr(i, 2))));

	}
	std::cout << ascii_string << std::endl;
	return ascii_string;
}

std::string File::checkTimeFormat(int time_unit) {
	std::string time = std::to_string(time_unit);
	if (time.length()<2) {
		time.push_back(time.at(0));
		time.at(0) = '0';
	}
	return time;
}

File::File(){}

File::File(std::string format, std::string magic) :format(format), magic(magic),
chsum("undefined"), time_stamp("undefined"), type("undefined"), compression("undefined"),  
magic_offset(0), magic_offset_size(0),os("undefined"),filesInside(0), size(0), network(1), arch("undefined")
{

}

void File::parseFile(std::string fileInBytes, File* file){}

void File::getInfo() {
	std::cout << "\n Name: " << this->name  << " magic: " << this->magic  <<" size: " << this->size << " chsum: " << this->chsum << " os: " << this->os
		<< "\n time_stamp: " << this->time_stamp << " format: " << this->format
		<< "\n type: " << this->type << " compression: " << this->compression
		<< "\n extension : " << this->extension << " filesInside: " << this->filesInside
		<< " network: " << this->network << " arch: " << this->arch;
}


void File::getNameAndExt(std::string filePath) {
	std::string fileName, fileExt, cutPath;
	std::regex reg(".+\\.\\w{2,10}");
	int pos = 0;
	//ищем имя файла в пути
	for (int i = 0; i <= filePath.length(); i++) {
		if (filePath[i] == '\\') {
			pos = i;
		}
	}
	pos++;
	cutPath = filePath.substr(pos);

	if (std::regex_match(cutPath, reg)) {
		for (int i = 0; i <= cutPath.length(); i++) {
			if (cutPath[i] == '.') {
				pos = i;
			}
		}
		pos++;
		fileName = cutPath.substr(0, pos-1);
		fileExt = cutPath.substr(pos);


		this->name = fileName;
		this->extension = fileExt;
	}
	else {
		this->name = cutPath;
		this->extension = "no";
	}

}

std::string File::convertHexToDec(std::string hexInString) {
	char tab2[1024];
	strncpy_s(tab2, hexInString.c_str(), sizeof(tab2));
	tab2[sizeof(tab2) - 1] = 0;
	int i, k, p;
	long long result = 0;
	p = strlen(tab2) - 1;
	for (i = 0; tab2[i] != '\0'; i++)
	{
		switch (toupper(tab2[i]))
		{
		case 'A': k = 10; break;
		case 'B': k = 11; break;
		case 'C': k = 12; break;
		case 'D': k = 13; break;
		case 'E': k = 14; break;
		case 'F': k = 15; break;
		case '1': k = 1; break;
		case '2': k = 2; break;
		case '3': k = 3; break;
		case '4': k = 4; break;
		case '5': k = 5; break;
		case '6': k = 6; break;
		case '7': k = 7; break;
		case '8': k = 8; break;
		case '9': k = 9; break;
		case '0': k = 0; break;
		}
		result = result + k * pow(16, p); //формула перевода из 16 СС в 10 СС
		p--;
	}
	return std::to_string(result);
}

int File::formatToInt() {
	if (this->format == "tar") {
		return 1;
	}
	else if (this->format == "gzip") {
		return 2;
	}
	else if (this->format == "zip") {
		return 3;
	}

	else if (this->format == "elf") {
		return 4;
	}
	else if (this->format== "pe") {
		return 5;
	}
	else if (this->format == "ico") {
		return 6;
	}
	else if (this->format == "gif") {
		return 7;
	}
	else if (this->format == "u-boot") {
		return 8;
	}
	else if (this->format == "squashfs") {
		return 9;
	}
	else if (this->format == "script") {
		return 10;
	}
	
	else {
		return 11;
	}
}

int File::compressionToInt(){
	if (this->compression == "deflate 08") {
		return 1;
	}
	else if (this->compression == "no") {
		return 2;
	}
	else {
		return 4;
	}
}

int File::typeToInt(){
	if (this->type == "archive") {
		return 1;
	}
	else if (this->type == "image") {
		return 2;
	}
	else if (this->type == "grafics") {
		return 3;
	}

	else if (this->type == "executable") {
		return 4;
	}
	else if (this->type == "realocatable") {
		return 5;
	}
	else if (this->type == "shared_object") {
		return 6;
	}
	else if (this->type == "driver") {
		return 7;
	}
	else if (this->type == "core_component") {
		return 8;
	}
	else if (this->type == "net") {
		return 9;
	}
	else if (this->type == "com") {
		return 10;
	}
	else {
		return 11;
	}

}

int File::osToInt() {
	if (this->os == "fat fs(ms-dos,os/2,nt/win32)") {
		return 1;
	}
	else if (this->os == "unix") {
		return 3;
	}
	else if (this->os == "vm/cms") {
		return 4;
	}
	
	else if (this->os == "vms(open vms)") {
		return 4;
	}
	else if (this->os == "Macintosh") {
		return 7;
	}
	else if (this->os == "NTFS filesystem(NT)") {
		return 2;
	}
	else if (this->os == "hpfs fs(os/2,nt)") {
		return 4;
	}
	else {
		return 6;
	}
}

int File::networkToInt() {  //доделать
	return 0; 
}

int File::archToInt() { //доделать
	return 0;
}

std::string File::getFormat() {
	return format;
}

std::string File::getMagic() {
	return magic;
}

int File::getMagicOffset() {
	return magic_offset;
}

int File::getMagicOffsetSize() {
	return magic_offset_size;
}

