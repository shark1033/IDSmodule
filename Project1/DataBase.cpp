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
	sqlite3_exec(this->db, this->Compression, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->Compression_insert, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->Type, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->Type_insert, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->Os, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->Os_insert, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->Formats, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->Formats_insert, 0, 0, &(this->err));
	//sqlite3_exec(this->db, this->Network, 0, 0, &(this->err));
	//sqlite3_exec(this->db, this->Network_insert, 0, 0, &(this->err));
	sqlite3_exec(this->db, this->Files, 0, 0, &(this->err));
}

void DataBase::selectInfo() {
	if (sqlite3_exec(this->db, this->Select, callback, (void*) data, &(this->err))) {
		fprintf(stderr, "\n ERROR SQL: %sn \n", err);
		sqlite3_free(err);
	}
}
//todo дописать выражение! добавить архитектуру
std::string DataBase::prepareInsertStatement(File* file) {

	std::string statement = "INSERT INTO Files(name, size, magic, extension, chsum, owner, date_changed, date_created, version, files_inside, network, type, os, compression, format) VALUES(";
	statement += "'" + file->name + "','" + std::to_string(file->size) + "','" + file->magic + "','" + file->extension + "','" + file->chsum + "','" + file->time_stamp + "','" + file->time_stamp
		+ "','" + std::to_string(file->filesInside) + "','" + std::to_string(file->network) + "','"
		+ std::to_string(file->typeToInt()) + "','" + std::to_string(file->osToInt()) + "','" + std::to_string(file->compressionToInt()) + "','" + std::to_string(file->formatToInt())+"');";
	return statement;
}

//DataBase::DataBase(){}

		
