#include "Elf.h"
#include <iostream>



Elf::Elf() {
	this->magic_offset_size = this->magic.length();
}

void Elf::parseFile(std::string fileInBytes, File* file) {
	getByteOrder(fileInBytes);
	getArchBit(fileInBytes);
	file->arch = getArch(fileInBytes);
	file->type = getType(fileInBytes);
	file->compression = "no";
	file->os = getOs(fileInBytes);
	getHeaderInfo(fileInBytes);


}


std::string Elf::getOs(std::string fileInBytes) {

	std::string os = fileInBytes.substr(14, 2);
	os = convertHexToDec(os);
	int bytes = std::stoi(os);

	
	if (bytes == 0) { return "unix"; }
	else if (bytes == 1) { return "hp_ux"; }
	else if (bytes == 2) { return "nx"; }
	else if (bytes == 3) { return "3gnu"; }
	else if (bytes == 4) { return "gnu"; }
	else if (bytes == 5) { return "86oc"; }
	else if (bytes == 6) { return "solaris"; }
	else if (bytes == 7) { return "monterey"; }
	else if (bytes == 8) { return "irix"; }
	else if (bytes == 9) { return "fx"; }
	else if (bytes == 10) { return "tru64"; }
	else if (bytes == 11) { return "novel"; }
	else if (bytes == 12) { return "open_bsd"; }
	else if (bytes == 13) { return "open_vms"; }
	else if (bytes == 14) { return "hp_nsk"; }
	else if (bytes == 97) { return "arm"; }
	else if (bytes == 255) { return "standalone"; }
	else { return "undefined"; }
}

std::string Elf::getArch(std::string fileInBytes) { //add values

	int arch = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(36, 4),2)));
	
	std::cout << arch;

	if (arch == 0) { return "unknown"; }
	else if (arch == 1) { return "at&t_we_32100"; }
	else if (arch == 2) { return "sparc"; }
	else if (arch == 3) { return "intel_80386"; }
	else if (arch == 4) { return "motorola_68000"; }
	else if (arch == 5) { return "motorola_88000"; }
	else if (arch == 6) { return "intel_80860"; }
	else if (arch == 7) { return "mips_rs300"; }
	else if (arch == 8) { return "mips_rs300_be"; }
	else if (arch == 9) { return "ibm_system/370_processor"; }
	else if (arch == 10) { return "mips_rs3000_le"; }
	else if (arch == 11) { return "rs6000"; }
	else if (arch == 15) { return "pa_risc"; }
	else if (arch == 16) { return "ncube"; }
	else if (arch == 17) { return "fujitsu vpp500"; }
	else if (arch == 18) { return "sun_sparc_32+"; }
	else if (arch == 19) { return "intel_80960"; }
	else if (arch == 20) { return "power_pc"; }
	else if (arch == 21) { return "power_pc64"; }
	else if (arch == 22) { return "ibm_system/390_processor"; }
	else if (arch == 36) { return "nex_v800"; }
	else if (arch == 37) { return "fujitsu fr20"; }
	else if (arch == 38) { return "trw_rh32"; }
	else if (arch == 39) { return "motorola_rce"; }
	else if (arch == 40) { return "advanced_risc_machines_arm"; }
	else if (arch == 41) { return "digital_alpha"; }
	else if (arch == 42) { return "hitachi_sh"; }
	else if (arch == 43) { return "sun_sperc_v9_64"; }
	else if (arch == 44) { return "siemens_tricore_embedded_processor"; }
	else if (arch == 45) { return "argonaut_risc_core"; }
	else if (arch == 46) { return "hitachi_h8/300"; }
	else if (arch == 47) { return "hitachi_h8/300h"; }
	else if (arch == 48) { return "hitachi_h8s"; }
	else if (arch == 49) { return "hitachi_h8/500"; }
	else if (arch == 50) { return "intel_ia64"; }
	else if (arch == 51) { return "stanford_mips_x"; }
	else if (arch == 52) { return "motorola_coldfire"; }
	else if (arch == 53) { return "motorola m68hc12"; }
	else if (arch == 54) { return "fujitsu_mma_multimedia_accelerator"; }
	else if (arch == 55) { return "siemens pcp"; }
	else if (arch == 56) { return "sony_ncpu_embedded_risc_processor"; }
	else if (arch == 57) { return "denso_ndr1_microprocessor"; }
	else if (arch == 58) { return "motorola_star*core_processor"; }
	else if (arch == 59) { return "toyota_me16_processor"; }
	else if (arch == 60) { return "stmicroelectronics_st100_processor"; }
	else if (arch == 61) { return "advanced_logic_corp"; }
	else if (arch == 62) { return "amds_x86-64_arch"; }
	else if (arch == 63) { return "sony_dsp_processor"; }
	else if (arch == 66) { return "siemens_fx66_microcontroller"; }
	else if (arch == 67) { return "stmicroelectronics_st9_8/16"; }
	else if (arch == 68) { return "stmicroelectronics_st7_8"; }
	else if (arch == 69) { return "motorola_mc68hc16_microcontroller"; }
	else if (arch == 70) { return "motorola_mc68hc11_microcontroller"; }
	else if (arch == 71) { return "motorola_mc68hc08_microcontroller"; }
	else if (arch == 72) { return "motorola_mc68hc05_microcontroller"; }
	else if (arch == 73) { return "silicon_graphics_cvx"; }
	else if (arch == 74) { return "stmicroelectronics_st19_8"; }
	else if (arch == 75) { return "digital_vax"; }
	else if (arch == 76) { return "axis_communications_32"; }
	else if (arch == 77) { return "infineon_technologies_32"; }
	else if (arch == 78) { return "element_14_64_dsp_processor"; }
	else if (arch == 79) { return "lsi_logic_16_dsp_processor"; }
	else if (arch == 80) { return "donald_knuth'_ educational_64"; }
	else if (arch == 81) { return "harvard_university_machine_independent_object_files"; }
	else if (arch == 82) { return "sitera_prism"; }
	else if (arch == 83) { return "atmel_avr_8_microcontroller"; }
	else if (arch == 84) { return "fujitsu_fr30"; }
	else if (arch == 85) { return "mitsubishi_d10v"; }
	else if (arch == 86) { return "mitsubishi_d30v"; }
	else if (arch == 87) { return "nec_v850"; }
	else if (arch == 88) { return "mitsubishi_m32r"; }
	else if (arch == 89) { return "matsushita_mn10300"; }
	else if (arch == 90) { return "matsushita_mn10200"; }
	else if (arch == 91) { return "pico_java"; }
	else if (arch == 92) { return "open_risk_32_embedded_processor"; }
	else if (arch == 93) { return "arc_core_tangent_a5"; }
	else if (arch == 94) { return "tensilica_xtensa_architecture"; }
	else if (arch == 95) { return "matsushita_mn10200"; }
	
	return "undefined";
}

std::string Elf::getType(std::string fileInBytes) {
	std::string type = fileInBytes.substr(32, 4);

	if (type == "0000") { return "unknown"; }
	else if (type == "0100") { return "object_file"; }
	else if (type == "0200") { return "executable"; }
	else if (type == "0300") { return "shared_lib"; }
	else if (type == "0400") { return "core_file"; }
	else if (type == "ff00") { return "d_on_cpu"; }
	else if (type == "ffff") { return "d_on_cpu"; }

	return "undefined";
}

std::string Elf::getChsum(std::string fileInBytes) {
	return "";
}

std::string Elf::getMagic() {
	return this->magic;
}

std::string Elf::getFormat() {
	return this->format;
}



int Elf::getMagicOffset() {
	return this->magic_offset;
}

int Elf::getMagicOffsetSize() {
	return this->magic_offset_size;
}



void Elf::getArchBit(std::string fileInBytes) {
	if (fileInBytes.substr(8, 2) == "02") {
		arch_bit = "64";
	}
	else { arch_bit = "32"; }
	std::cout << "arch: " << arch_bit << std::endl;
}

void Elf::isCoreFile(std::string sub) {

	if (sub == "init_module" || sub == "cleanup_module") {
		type = "core_file";
	}
}

void Elf::getByteOrder(std::string fileInBytes) {
	if (fileInBytes.substr(10, 2) == "02") {
		isBigEndian = true;
		std::cout << "bigEndian"<<std::endl;
	}
	else { isBigEndian = false; std::cout << "littleEndian"<<std::endl; }
}

void Elf::getHeaderInfo(std::string fileInBytes) {

	if (arch_bit == "32") {
		if (!isBigEndian) {
			sht_offset = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(64, 8), 4)));
			sh_ent_size = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(92, 4), 2)));
			sh_num = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(96, 4), 2)));
			sh_str_ndx = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(100, 4), 2)));
		}
		else {
			sht_offset = std::stoi(convertHexToDec(fileInBytes.substr(64, 8)));
			sh_ent_size = std::stoi(convertHexToDec(fileInBytes.substr(92, 4)));
			sh_num = std::stoi(convertHexToDec(fileInBytes.substr(96, 4)));
			sh_str_ndx = std::stoi(convertHexToDec(fileInBytes.substr(100, 4)));

		}
	}
	else if (arch_bit == "64") { //для 64 биьной архитектуры
		std::cout <<isBigEndian << std::endl;
		if (!isBigEndian) { //если порядок байтов не биг эндиан, то конвертируем
			sht_offset = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(80, 16), 8)));
			sh_ent_size = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(116, 4),2)));
			sh_num = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(120, 4), 2)));
			sh_str_ndx = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(124, 4), 2)));
		}
		else {
			sht_offset = std::stoi(convertHexToDec(fileInBytes.substr(80, 16)));
			sh_ent_size = std::stoi(convertHexToDec(fileInBytes.substr(116, 4)));
			sh_num = std::stoi(convertHexToDec(fileInBytes.substr(120, 4)));
			sh_str_ndx = std::stoi(convertHexToDec(fileInBytes.substr(124, 4)));
		}
		sh_str_tab_offset = sht_offset + (sh_str_ndx * sh_ent_size); 
	}
	std::cout << "section header table offset: " << sht_offset << std::endl;
	std::cout << "section header entity size: " << sh_ent_size << std::endl;
	std::cout << "section header number of entities: " << sh_num << std::endl;
	std::cout << "section header str tab index: " << sh_str_ndx << std::endl;
	std::cout << "section header str tab offset: " << sh_str_tab_offset << std::endl;
}

void Elf::getStrabOffset() {
	str_tab_structure_offset = sht_offset + (str_tab_section_index * sh_ent_size);
	std::cout << "offset to section dynstr "<<str_tab_structure_offset << std::endl;
}

void Elf::getStrTabIndex(std::string fileInBytes) {
	
	std::string sub, temp, expression;
	int counter = 2;
	int index = 0;
	char check;
	int condition = sh_str_tab_section_size * 2;
	
	for (int i = 0; i < sh_num; i++) {

		while (counter<=condition) {      //70 00

			check = fileInBytes.at(counter - 1);
			temp.push_back(fileInBytes.at(counter));

			//std::cout << "check          " << check << std::endl;
			//std::cout << "temp0          " << temp << std::endl;

			temp.push_back(fileInBytes.at(counter+1));
			
			
			//std::cout << "temp0+1        " << temp << std::endl;


			if (temp == "00"  && (counter+1)%2!=0) {
				counter += 2;
				break;
			}
			//std::cout << counter << std::endl;
			sub += fileInBytes.at(counter);
			counter++;

			temp.clear();
		}
		std::cout << "sub          " << sub << std::endl;
		expression = convertBytesToAscii(sub);
		if (expression == ".dynstr" || expression == ".strtab" ) {
			str_tab_section_index = index;
			break;
		}
		
		index++;
		std::cout << "index          " << index << std::endl;
		sub.clear();
		expression.clear();
	}

	getStrabOffset();

}

void Elf::getShStrTabOffsetAndSize(std::string fileInBytes) { //fileInBytes.lenght() = 128 or 64 
	

	if (arch_bit == "64") {
		if (!isBigEndian) {
			sh_str_tab_section_offset = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(48, 16),8)));
			sh_str_tab_section_size = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(64, 16), 8)));
		}
		else {
		sh_str_tab_section_offset = std::stoi(convertHexToDec(fileInBytes.substr(48, 16)));
		sh_str_tab_section_size = std::stoi(convertHexToDec(fileInBytes.substr(64, 16)));
		}
	}
	else {
	if (!isBigEndian) {
		sh_str_tab_section_offset = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(32, 8), 4)));
		sh_str_tab_section_size = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(40, 8), 4)));
	}
	else {
		sh_str_tab_section_offset = std::stoi(convertHexToDec(fileInBytes.substr(32, 8)));
		sh_str_tab_section_size = std::stoi(convertHexToDec(fileInBytes.substr(40, 8)));
	}
	}
	std::cout << "sh_str_tab_section_offset = " << sh_str_tab_section_offset << std::endl;
	std::cout << "sh_str_tab_section_offset = " << sh_str_tab_section_size << std::endl;


}

void Elf::getStrTabSectionOffsetAndSize(std::string fileInBytes) {
	if (arch_bit == "64") {
		if (!isBigEndian) {
			str_tab_section_offset = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(48, 16), 8)));
			str_tab_section_size = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(64, 16), 8)));
		}
		else {
			str_tab_section_offset = std::stoi(convertHexToDec(fileInBytes.substr(48, 16)));
			str_tab_section_size = std::stoi(convertHexToDec(fileInBytes.substr(64, 16)));
		}
	}
	else {
		if (!isBigEndian) {
			str_tab_section_offset = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(32, 8), 4)));
			str_tab_section_size = std::stoi(convertHexToDec(convertBigEndian(fileInBytes.substr(40, 8), 4)));
		}
		else {
			str_tab_section_offset = std::stoi(convertHexToDec(fileInBytes.substr(32, 8)));
			str_tab_section_size = std::stoi(convertHexToDec(fileInBytes.substr(40, 8)));
		}
	}
	std::cout << "sh_str_tab_section_offset = " << str_tab_section_offset << std::endl;
	std::cout << "sh_str_tab_section_offset = " << str_tab_section_size << std::endl;

}

void Elf::defineNetworkMode(std::string fileInBytes) {


	std::string sub, temp, expression;
	int counter = 2;
	int index = 0;
	char check;
	int condition = str_tab_section_size * 2;


	while (counter <= condition) {      // or < ??

		check = fileInBytes.at(counter - 1);
		temp.push_back(fileInBytes.at(counter));

		//std::cout << "check          " << check << std::endl;
		//std::cout << "temp0          " << temp << std::endl;

		temp.push_back(fileInBytes.at(counter + 1));


		//std::cout << "temp0+1        " << temp << std::endl;


		if (temp == "00" && (counter + 1) % 2 != 0) {
			counter += 2;
			std::cout << "substring is:   " << sub << std::endl;
			expression = convertBytesToAscii(sub);


			if (isEqualed(expression)) {
				network = 1;
				break;
			}
			sub.clear();
			temp.clear();
			expression.clear();

		}
		temp.clear();

		//std::cout << counter << std::endl;
		sub += fileInBytes.at(counter);
		counter++;
	}
	
}


bool Elf::isEqualed(std::string sub) {

	for (int i = 0; i < sizeof(net_array); i++){
		if (sub == net_array[i]) {
			std::cout << "True" << std::endl;
			return true;
		}

	}
	std::cout << "False" << std::endl;
	isCoreFile(sub);
	return false;


}