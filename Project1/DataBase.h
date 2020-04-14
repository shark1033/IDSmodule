#pragma once
#include "sqlite3.h"
#include <string>
#include "File.h"
class DataBase
{
public:
	std::string dbPath;
	sqlite3* db=0; // хэндл объекта соединение к БД
	char* err = 0;
	const char* expression;
	const char* data = "Callback function called";

	const char* compression = "CREATE TABLE IF NOT EXISTS Compression(id   INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR);";
	const char* compression_insert = "INSERT INTO Compression(name) VALUES ('deflate'),('no'),('undefined'),('other');"; //add new compression methods
	
	const char* type = "CREATE TABLE IF NOT EXISTS Type(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR);";
	const char* type_insert ="INSERT INTO Type(name) VALUES ('archive'), ('image'), ('grafic'), "
		"('executable'), ('relocatable'), ('shared_object'), ('driver'), ('core_component'), ('net'), ('com');";

	const char* arch = "CREATE TABLE IF NOT EXISTS Arch(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR);";
	const char* arch_insert = "INSERT INTO Arch(name) VALUES ('archive'), ('image'), ('grafic'), " //change
		"('executable'), ('relocatable'), ('shared_object'), ('driver'), ('core_component'), ('Net'), ('COM');";

	const char* os = "CREATE TABLE IF NOT EXISTS Os(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR);";
	const char* os_insert ="INSERT INTO Os(name) VALUES ('ms-dos, os/2, nt/win32)'), ('windows'),"
		"('unix'), ('macintosh'), ('no'), ('other'), ('undefined');";

	const char* network = "CREATE TABLE IF NOT EXISTS Network(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR);";
	const char* network_insert ="INSERT INTO Network(name) VALUES ('true'), ('false'), ('undefined');";

	const char* formats = "CREATE TABLE IF NOT EXISTS Formats(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR);";
	const char* formats_insert ="INSERT INTO Formats(name) VALUES('tar'), ('gzip'), ('zip'), ('elf'), ('pe'), ('ico'), ('gif'), ('uboot'), ('squashfs'), ('script'), ('undefined');"; //uboot!!!
	
	const char* files="CREATE TABLE IF NOT EXISTS Files(id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"    // запрос на создание таблицы Files. Выполняется после создания всех отсльаных таблиц
            "name VARCHAR, size VARCHAR, magic VARCHAR, extension VARCHAR, chsum VARCHAR,  time_stamp VARCHAR,"
            "files_inside INT, type INT REFERENCES Type(id), os INT REFERENCES Os(id), "
			"compression INT REFERENCES Compression(id), format INT REFERENCES Formats(id), network INT REFERENCES Network(id)), arch INT REFERENCES Arch(id);"; 

	const char* Delete = "DELETE * FROM Files;";   //удалить все записи из Files


	const char* Select="SELECT Files.name , Files.size, files.magic, Files.extension, Files.chsum,"
		"Files.owner, Files.time_stamp, Files.files_inside, Files.network, "
		"Os.name as os, Type.name as type, Compression.name as compression, Formats.name as format, Arch.name as arch, Network.name as network "
		"FROM Files "
		"INNER JOIN Formats on "
		"Files.format = Formats.id "
		"INNER JOIN Os on "
		"Files.os = Os.id "
		"INNER JOIN Type on "
		"Files.type = Type.id "
		"Inner JOIN Compression on " 
		"Files.compression = Compression.id"
		"Inner JOIN Arch on " 
		"Files.arch = Arch.id"
		"Inner JOIN Network on " 
		"Files.network = Network.id";
		


	std::string prepareInsertStatement(File* file);

	static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
		int i;
		for (i = 0; i < argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}
		printf("\n");
		return 0;
	}

	void selectInfo();

	void connect();
	void disconnect();

	void createDatabases();
	void deleteTableFiles();
	void insertIntoTables(const char* expression);
	void updateTables();
	void deleteFromTables();

	DataBase(std::string dbPath="defoltDB.sqlite3");
	~DataBase();

};

