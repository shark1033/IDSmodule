#include "DataBase.h"
#include "sqlite3.h"
#include <iostream>


void DataBase::connect() {
	if (sqlite3_open(this->dbPath.c_str(), &(this->db))) {
		fprintf(stderr, "Failed to open/create DB: %s\n", sqlite3_errmsg(db));
	}
	else{std::cout << "connection is opened sucsessfully"; }
	
}

void DataBase::disconnect() {
	sqlite3_close(this->db);
	std::cout << "connection is closed";
}

DataBase::DataBase(std::string dbPath) : dbPath(dbPath) {}

DataBase::~DataBase() {
	//std::cout << "\n"<<"object DataBase was deleted"<<"\n";
}

void DataBase::insertIntoTables(const char* expression) {

	if (sqlite3_exec(this->db, expression, 0, 0, &(this->err))) {
		fprintf(stderr, "\n ERROR SQL: %sn", err);
				sqlite3_free(err);
		}
	}
	
void DataBase::createDatabases() {
	sqlite3_exec(this->db, this->compression, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->compression_insert, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->type, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->type_insert, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->os, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->os_insert, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->formats, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->formats_insert, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->network, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->network_insert, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->files, 0, 0, &(this->err));
}

void DataBase::selectInfo() {
	if (sqlite3_exec(this->db, this->Select, callback, (void*) data, &(this->err))) {
		fprintf(stderr, "\n ERROR SQL: %sn \n", err);
		sqlite3_free(err);
	}
}
//todo дописать выражение! добавить архитектуру
std::string DataBase::prepareInsertStatement(File* file) {

	std::string statement = "INSERT INTO Files(name, size, magic, extension, chsum, time_stamp, files_inside, type, os, compression, format,  network, arch) VALUES(";
	statement += "'" + file->name + "','" + std::to_string(file->size) + "','" + file->magic + "','" + file->extension + "','" + file->chsum + "','" + file->time_stamp 
		+ "','" + std::to_string(file->filesInside) + "','" 
		+ std::to_string(file->typeToInt()) + "','" + std::to_string(file->osToInt()) + "','" + std::to_string(file->compressionToInt()) + "','" + std::to_string(file->formatToInt())+ 
		"','" + std::to_string(file->networkToInt()) + "','" +std::to_string(file->archToInt()) + "');";
		
	return statement;
}

//DataBase::DataBase(){}

		
