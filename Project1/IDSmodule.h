#pragma once
#include <string>
#include "File.h"
#include "DataBase.h"
#include <fstream> 



class IDSmodule
{
public:
    File file;
    File* formatObjects[9];
    DataBase db;

    std::string fileInBytes;
    std::string filePath; 

    unsigned long long lenght;

    std::string readCharachters(int start_pos, int counter);
    std::string readFile(int start_pos, int counter);

    bool isOtherFormat(std::string format);

    void checkFormat();
    void getInfo(std::string format, int pointer);
    
    IDSmodule(std::string filePath, std::string dbPath = "defolt.dblite" );
    ~IDSmodule();
    

};