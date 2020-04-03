#pragma once
#include <string>
#include "File.h"
#include "DataBase.h"
#include <vector>
#include <fstream> //////!!!!!!!!!!!!!!!!!!!



class IDSmodule
{
public:
    File file;
   // std::vector<File>files;
    File* formatObjects[7];
    DataBase db;
    //void initArray();
    std::string fileInBytes;
    std::string fileInCharacters;
   // std::string fileContent;
    std::string filePath; //"s:\\testfiles\\example.gz";
    unsigned long long lenght;
    

    std::string readFile(int start_pos, int counter);
    void checkFormat();
    void getInfo(std::string format, int pointer);

    //std::string readBytes(int start_pos, int counter);
    std::string readCharachters(int start_pos, int counter);


    IDSmodule(std::string filePath, std::string dbPath = "defolt.dblite" );
    ~IDSmodule();
    

};