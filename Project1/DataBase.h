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

	const char* Compression = "CREATE TABLE IF NOT EXISTS Compression(id   INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR);";
	const char* Compression_insert = "INSERT INTO Compression(name) VALUES ('Deflate'),('No'),('Undefined'),('Other');";
	
	const char* Type = "CREATE TABLE IF NOT EXISTS Type(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR);";
	const char* Type_insert ="INSERT INTO Type(name) VALUES ('archive'), ('image'), ('grafic'), "
		"('executable'), ('relocatable'), ('shared_object'), ('driver'), ('core_component'), ('Net'), ('COM');";

	const char* Os = "CREATE TABLE IF NOT EXISTS Os(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR);";
	const char* Os_insert ="INSERT INTO Os(name) VALUES ('Fat (MS-DOS, OS/2, NT/Win32)'), ('NTFS (NT)'),"
		"('Unix'), ('Other'), ('No'), ('Undefined'), ('Macintosh');";

	//const char* Network = "CREATE TABLE IF NOT EXISTS Network(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR);";
	//const char* Network_insert ="INSERT INTO Network(name) VALUES ('no'), ('yes');";

	const char* Formats = "CREATE TABLE IF NOT EXISTS Formats(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR);";
	const char* Formats_insert ="INSERT INTO Formats(name) VALUES('Tar'), ('Gzip'), ('Zip'), ('Elf'), ('Pe'), ('Ico'), ('Gif'), ('U-boot'), ('Squashfs'), ('Script'), ('Undefined');";
	
	const char* Files="CREATE TABLE IF NOT EXISTS Files(id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"    // запрос на создание таблицы Files. Выполняется после создания всех отсльаных таблиц
            "name VARCHAR, size VARCHAR, magic VARCHAR, extension VARCHAR, chsum INT, owner VARCHAR, date_changed VARCHAR, date_created VARCHAR,"
            "version VARCHAR, files_inside INT, type INT REFERENCES Type(id), os INT REFERENCES Os(id), "
			"compression INT  REFERENCES Compression(id), format INT REFERENCES Formats(id), network INT);";

	const char* Delete = "DELETE * FROM Files;";   //удалить все записи из Files


	const char* Select="SELECT Files.name , Files.size, Files.magic, Files.extension, Files.chsum,"
		"Files.owner, Files.date_changed, Files.date_created, Files.version, Files.files_inside, Files.network, "
		"Os.name as os, Type.name as type, Compression.name as compression, Formats.name as format "
		"FROM Files "
		"INNER JOIN Formats on "
		"Files.format = Formats.id "
		"INNER JOIN Os on "
		"Files.os = Os.id "
		"INNER JOIN Type on "
		"Files.type = Type.id "
		"Inner JOIN Compression on " 
		"Files.compression = Compression.id";


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
	//DataBase();
	~DataBase();

};

