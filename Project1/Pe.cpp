#include "Pe.h"
#include <iostream>



Pe::Pe() {
	this->magic_offset_size = this->magic.length();
}

int Pe::getPeHeader(std::string fileInBytes) {
	std::cout << "Pe";
	std::string e_lfanew=convertBigEndian(fileInBytes, 4);
	pe_offset = std::stoi(convertHexToDec(e_lfanew));
	std::cout << fileInBytes << " " << pe_offset;
	return pe_offset;
}

void Pe::parseFile(std::string fileInBytes, File* file) {
	file->time_stamp = getTime(fileInBytes);
	file->arch = getArch(fileInBytes);
	number_of_sections = getNumbOfSec(fileInBytes);
	getSizeOfOh(fileInBytes);
	file->os = "windows";
	file->compression = "no";
}

int Pe::getMagicOffsetSize() {
	return this->magic_offset_size;
}

int Pe::getMagicOffset() {
	return this->magic_offset;
}

int Pe::getNumbOfSec(std::string fileInBytes) {
	std::string st = fileInBytes.substr(12, 4);
	st = convertBigEndian(st, 2);

	return std::stoi(st);
}

std::string Pe::getMagic() {
	return this->magic;
}

std::string Pe::getFormat() {
	return this->format;
}

std::string Pe::getTime(std::string fileInBytes) {
	std::string t = fileInBytes.substr(16, 8);
	if (t == "00000000") {
		return "undefined";
	}
	t=convertBigEndian(t, 4);
	t=convertTime(t);
	return t;
}

std::string Pe::getArch(std::string fileInBytes) {
	std::string ar = fileInBytes.substr(8, 4);
	ar = convertBigEndian(ar, 2);
	int arc = stoi(convertHexToDec(ar));

	switch (arc)
	{
		case 0: return "unknown";
		case 332: return "intel 80386";
		case 333: return "intel 80486";
		case 334: return "intel pentium";
		case 352: return "mips r3000_be";
		case 354: return "mips r3000_le";
		case 358: return "mips r4000_le";
		case 360: return "mips r1000";
		case 361: return "mips wce v2";
		case 388: return "dec";
		case 418: return "hitachi sh3";
		case 419: return "hitachi sh3e";
		case 420: return "hitachi sh4";
		case 422: return "hitachi sh5";
		case 448: return "arm";
		case 450: return "arm thumb";
		case 452: return "arm thumb_le";
		case 467: return "panasinic am33";
		case 496: return "ibm power_pc_le";
		case 497: return "ibm power_pc fp";
		case 512: return "itanium";
		case 614: return "mips16";
		case 616: return "mototola 68000";
		case 644: return "dec/compaq alpha axp 64-bit";
		case 870: return "mips with fpu";
		case 1126: return "mips16 with fpu";
		case 1312: return "infineon tricore";
		case 3772: return "efi byte code";
		case 3773: return "efi byte code";
		case 20530: return "risc32";
		case 20580: return "risc64";
		case 20776: return "risc128";
		case 34404: return "amd 64";
		case 36929: return "Mitsubishi M32R_le";
		case 43620: return "arm64_le";


		default: return "undefined";
	}
}

bool Pe::isDriver(std::string fileInBytes) {
	std::string subsystem = convertBigEndian(fileInBytes.substr(136, 4),2);
	int sub = std::stoi(subsystem);
	std::cout << "sub  "<<sub << std::endl;
	if (sub == 1) return true;
	else if (sub == 8) return true;
	else if (sub == 12) return true;
	else return false;

}

bool Pe::isCOM() {
	if (idd.at(0).size != 0 && idd.at(0).size != 0) {
		return true;
	}
	else return false;

}

bool Pe::isNet() {
	if (idd.at(14).size != 0 && idd.at(14).size != 0) {
		return true;
	}
	else return false;
}

std::string Pe::getChsum(std::string fileInBytes) {
	std::string chsm = convertBigEndian(fileInBytes.substr(128, 8),4);
	return chsm;
}

void Pe::getArchBit(std::string fileInBytes) {
	std::string archbit = fileInBytes.substr(fileInBytes.length() - 4);
	archbit = convertBigEndian(archbit, 2);
	if (archbit == "010b") {
		arch_bit="pe32";
	}
	else if (archbit == "020b") {
		arch_bit="pe32+";
	}
	else {
		
		arch_bit = "undefined";
	}
}

void Pe::getImageBase(std::string fileInBytes) {

	std::string ib;

	if (arch_bit == "pe32") {
		ib = fileInBytes.substr(56, 8);
		ib = convertBigEndian(ib, 4);
		ib = convertHexToDec(ib);
		image_base = std::stoi(ib);
	}
	else {
		ib = fileInBytes.substr(56, 16);
		ib = convertBigEndian(ib, 8);
		ib = convertHexToDec(ib);
		image_base = std::stoi(ib);
	}
	
}

void Pe::getSectAlig(std::string fileInBytes) {

	int sectAlig = std::stoi(convertHexToDec((convertBigEndian(fileInBytes.substr(72, 8),4))));
	
}

void Pe::getSizeOfOh(std::string fileInBytes) {
	std::string s = fileInBytes.substr(40, 4);
	s = convertBigEndian(s, 2);
	s = convertHexToDec(s);
	size_of_optional_header = std::stoi(s);
	//std::cout <<"sooh   "<< size_of_optional_header << std::endl;
}

void Pe::getIDD(std::string fileInBytes) {
	std::string dirs;

	int offset;
	int start = 0;
	int end = 8;

	IMAGE_DATA_DIRECTORY idd_struct;


	if (arch_bit == "pe32") {
		offset = 192;
	}
	else { offset = 224; }

	//std::cout << "offset to idd is " << offset << std::endl;

	dirs = fileInBytes.substr(offset);
	for (int i = 0; i < 16; i++) {
		idd.push_back(idd_struct);

		idd.at(i).virtualAddress = std::stoi(convertHexToDec(convertBigEndian(dirs.substr(start, end),4)));

		start = end;
		end += 8;

		idd.at(i).size = std::stoi(convertHexToDec(convertBigEndian(dirs.substr(start, end), 4)));

		start = end;
		end += 8;

		//std::cout << "idd VA =  " << idd.at(i).virtualAddress << "idd size = " << idd.at(i).size << std::endl;
	}
}

std::string Pe::getType(std::string fileInBytes) {
	if (isNet()){ 
		return "net";
	}
	else if (isCOM()) {
		return "com";
	}
	else if (isDriver(fileInBytes)) {
		return "driver";
	}
	else {
		return "executable"; 
	}
}