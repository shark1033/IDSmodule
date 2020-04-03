#include "Gzip.h"
#include <string>
#include <iostream>
#include <vector>
#include <math.h>



Gzip::Gzip() {
	this->magic_offset_size = this->magic.length();
}

std::string Gzip::getFormat() {
	return this->format;
}
std::string Gzip::getMagic() {
	return this->magic;
}
int Gzip::getMagicOffset() {
	return this->magic_offset;
}
int Gzip::getMagicOffsetSize() {
	return this->magic_offset_size;
}
std::string Gzip::getType() {
	return this->type;
}

std::string Gzip::getOS(std::string fileInBytes) {
	int s = std::stoi(fileInBytes.substr(18, 2));
	switch (s)
	{
	case 0: return "fat fs(ms-dos,os/2,nt/win32)";
	case 2: return "vms(open vms)";
	case 3: return "unix";
	case 4: return "vm/cms";
	case 6: return "hpfs fs(os/2,nt)";
	case 7: return "Macintosh";
	case 11:return "NTFS filesystem(NT)";
	default:return "unknown";
	}
}

std::string Gzip::getChsum(std::string fileInBytes) {
	int start = fileInBytes.length() - 16;
	std::cout << "\n" << " start at " << start;
	std::cout << "\n" << fileInBytes.length() << "\n";
	std::string str = fileInBytes.substr(start, 8);
	std::string sub1, sub2, sub3, sub4;
	sub1 = str.substr(0, 2);
	sub2 = str.substr(2, 2);
	sub3 = str.substr(4, 2);
	sub4 = str.substr(6, 2);
	chsum = sub4 + sub3 + sub2 + sub1;
	char tab2[1024];
	strncpy_s(tab2, chsum.c_str(), sizeof(tab2));
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
		result = result + k * pow(16, p); //формула перевода из 16 —— в 10 ——
		p--;
	}
	
	return std::to_string(result);
}


long double Gzip::getSize(std::string fileInBytes) {
	if (compressed_size == 0) return 0;

	int start = fileInBytes.length() - 8;
	std::cout << "\n start at " << start;
	std::cout << "\n" << fileInBytes.length() << "\n";
	std::string size = fileInBytes.substr(start, 8);
	std::cout << "\n" << size << "\n";
	std::string sub1, sub2, sub3, sub4;
	sub1 = size.substr(0, 2);
	sub2 = size.substr(2, 2);
	sub3 = size.substr(4, 2);
	sub4 = size.substr(6, 2);
	size = sub4 + sub3 + sub2 + sub1;
	std::cout << "\n" << size << "\n";

	char tab2[1024];
	strncpy_s(tab2, size.c_str(), sizeof(tab2));
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
		result = result + k * pow(16, p); //формула перевода из 16 —— в 10 ——
		p--;
	}
	long double l1 = 2;
	long double l2 =32;
	long double resultd = pow(l1, l2);
	int rs = fmod(result, resultd); 
	size = std::to_string(rs);
	return rs;
}
std::string Gzip::getCompesion(std::string fileInBytes) {
	std::string s=fileInBytes.substr(4, 2);
	if (s == "08") return "deflate (08)";
}


std::string Gzip::getTime(std::string fileInBytes) {
	std::string s = fileInBytes.substr(8, 8); //получили подстроку (4 байт) времени
	//делаем из big endian -> little endian
	std::string sub1, sub2,sub3,sub4; 
	sub1 = s.substr(0, 2); //sub1->4 sub2->3 sub3->2 sub4->1
	sub2 = s.substr(2, 2);
	sub3 = s.substr(4, 2);
	sub4 = s.substr(6, 2);
	s = sub4 + sub3 + sub2 + sub1;
	
	//перевод string в массив char
	char tab2[1024];
	strncpy_s(tab2, s.c_str(), sizeof(tab2));
	tab2[sizeof(tab2) - 1] = 0;

	std::cout << "unix time:  " << tab2 << "\n";

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
		result = result + k * pow(16, p); //формула перевода из 16 —— в 10 ——
		p--;
	}

	std::cout << "unix time in dec:  " << result << "\n";

	//конвертаци€ значени€ времени из unix формата в обычный 
	std::string years,month,days,hours,minutes,seconds;
	int year, day, hour, minute, second, extra_days, days_minus_leap_days, extra, days_this_year;
	
	year=result/31436000+1970; //года с 1970 + 1970 = текущий год
	extra_days = (year - 1969) / 4; //доп дни в св€зи с весокосными годами
	day = result / 86400; //дней после 1970
	days_minus_leap_days = day - extra_days; //минус весокосные дни
	days_this_year = days_minus_leap_days % 365; // дней в этом году

	//структура описывает мес€ца
	struct Month
	{
		std::string name;
		int days;
	};

	std::vector<Month> months{
		{ "Jan", 31 }, { "Feb", 28 }, { "Mar", 31 }, { "Apr", 30 }, { "May", 31 }, { "Jun", 30 },
		{ "Jul", 31 }, { "Aug", 31 }, { "Sep", 30 }, { "Oct", 31 }, { "Nov", 30 }, { "Dec", 31 } };

	//проверка на високосный год
	bool leaf_year=false;
	if (year % 4==0 && year % 100 != 0|| year % 400==0) {
			leaf_year = true;
			months.at(1).days = 29;  //если високосный, то +1 к дн€м в феврале
			days_this_year++;		//нужно прибавить, иначе неправильный день
	}

	for (const auto& it : months){
		
		if (days_this_year == 0) {
			days_this_year = it.days;  //если при вычитании получили 0=>день равен числу дней в мес€це
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
	second=result - (day * 86400); //секунды в общем
	hour = second / 3600; //часы
	extra = (second-(hour * 3600));
	minute = extra / 60;//минуты
	second = extra - (minute * 60);//секунды

	std::cout << hour << ":" << minute << ":" << second << " " << days_this_year <<"/"<< month << "/" << year;
	std::string time = std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second) + " " + std::to_string(days_this_year) + "/" + month+"/" + std::to_string(year);
	return time;
}
void Gzip::parseFile(std::string fileInBytes, File* file) {

	file->compression = getCompesion(fileInBytes);
	file->date_created= getTime(fileInBytes);
	file->os=getOS(fileInBytes);
	file->chsum = getChsum(fileInBytes);
	file->compressed_size=getSize(fileInBytes); 
	file->type = getType();
	file->filesInside = 1; //gzip always contains 1 file inside itself
	

}


//todo getName, getChsum