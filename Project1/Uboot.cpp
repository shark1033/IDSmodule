#include "Uboot.h"


Uboot::Uboot() {
	this->magic_offset_size = this->magic.length();
}


void Uboot::parseFile(std::string fileInBytes, File* file) {
    file->arch = getArch(fileInBytes);
    file->compression = getCompression(fileInBytes);
    file->chsum = getChsum(fileInBytes);
    file->os = getOS(fileInBytes);
    file->date_created = getTime(fileInBytes);
    file->type = this->type;
}


std::string Uboot::getMagic() {
	return this->magic;
}

std::string Uboot::getFormat() {
	return this->format;
}

int Uboot::getMagicOffset() {
	return this->magic_offset;
}

int Uboot::getMagicOffsetSize() {
	return this->magic_offset_size;
}

std::string Uboot::getOS(std::string fileInBytes) {
	std::string os = fileInBytes.substr(56, 2);
	int bytes = std::stoi(os);

    if (bytes > 21) {
        return "undefined";
    }

    switch (bytes)
    {
        case 0: return "invalid";
        case 1: return "openbsd"; //os
        case 2: return "netbsd";  //os
        case 3: return "freebsd"; //os
        case 4: return "bsd4_4";  //os 
        case 5: return "linux";   //os
        case 6: return "svr4";  //outdated os
        case 7: return "esix";  //what is it?
        case 8: return "solaris"; //os
        case 9: return "irix";    //outdated os
        case 10: return "sco";    //outdated os, the developer became a bankrupt:(  
        case 11: return "dell";   //probably dell's firmware or os
        case 12: return "ncr";    //probably os for industrial devices
        case 13: return "lynxos"; //real time os
        case 14: return "vxworks";// os
        case 15: return "psos";   //real-time os
        case 16: return "qnx";    // real-time os
        case 17: return "u_boot";//firmware???
        case 18: return "rtems"; //real-time os
        case 19: return "artos"; //os
        case 20: return "unity"; //os by China
        case 21: return "integrity"; //what is it??
    }
}

std::string Uboot::getChsum(std::string fileInBytes) {
    std::string crc = fileInBytes.substr(8, 8); 
    
	return  crc; // пока что в таком виде. Далее надо разбираться с crc32, переводит из 16 в 10 СС с помощью convertHexToDec и выполнять какие-то действия. 
}

std::string Uboot::getCompression(std::string fileInBytes) { 
    std::string compression = fileInBytes.substr(62, 2);
    int bytes = std::stoi(compression);
    switch (bytes)
    {
    case 0: return "no";
    case 1: return "gzip";
    case 2: return "bzip2";
    case 3: return "lzma";
    case 4: return "lzo";

    default:
        return "undefined";
    }
}

std::string Uboot::getTime(std::string fileInBytes) {
	std::string unixTime = fileInBytes.substr(16, 8);
	return convertTime(unixTime);
}

std::string Uboot::getType() {
	return this->type;
}

std::string Uboot::getArch(std::string fileInBytes) {
    std::string archInfo = fileInBytes.substr(58, 2);
    int bytes = std::stoi(archInfo);
    switch (bytes)
    {
    case 0: return "invalid";
    case 1: return "alpha";
    case 2: return "arm";
    case 3: return "i386";//Intel x86
    case 4: return "ia64";
    case 5: return "mips";
    case 6: return "mips64";//MIPS 64 Bit
    case 7: return "ppc"; //PowerPC
    case 8: return "s390"; //IBM S390
    case 9: return "sh"; //SuperH
    case 10: return "sparc";
    case 11: return "sparc64"; //Sparc 64 Bit
    case 12: return "m68k";
    case 13: return "nios";
    case 14: return "microblaze";
    case 15: return "nios2";
    case 16: return "blackfin";
    case 17: return "avr32";
    case 18: return "st200"; //STMicroelectronics ST200
    default: return "undefined";
    }
}