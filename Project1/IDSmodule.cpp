#include "IDSmodule.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include "File.h"
#include "Zip.h"
#include "Gzip.h"
#include "Script.h"
#include "Gif.h"
#include "Ico.h"
#include "Squashfs.h"
#include "Uboot.h"
#include "Tar.h"
#include "Pe.h"
#include "DataBase.h"
#include <fstream>


    IDSmodule::IDSmodule(std::string filePath, std::string dbPath) {
        
        this->formatObjects[0] = new Ico();
        this->formatObjects[1] = new Script();
        this->formatObjects[2] = new Gif();
        this->formatObjects[3] = new Gzip();
        this->formatObjects[4] = new Zip();
        this->formatObjects[5] = new Squashfs();
        this->formatObjects[6] = new Uboot();
        this->formatObjects[7] = new Tar();
        this->formatObjects[8] = new Pe();
        this->db = DataBase(dbPath);
        this->filePath = filePath;
    };


    IDSmodule::~IDSmodule() {};


   
    bool IDSmodule::isOtherFormat(std::string format) {
        if (format == "ico" || format == "tar" || format == "gif" || format == "script") { return false; }
        return true;
    }


    std::string IDSmodule::readFile(int start_pos, int counter) {
        std::ifstream fileIn(this->filePath, std::ios::in | std::ios::binary);
 
        if (!fileIn.is_open())
        {
            std::cout << "Can not open file \"" << '\"' << std::endl;
            return "Error";
        }
        //длина файла
        fileIn.seekg(0, fileIn.end);
        long double lenght = fileIn.tellg();
        //курсор в начало файла 
        fileIn.seekg(start_pos, fileIn.beg);
        this->lenght = lenght;

        char sym;
        int count = 0;
        int currentByte = 0;
        std::string fileInByte;
        char sstring[3];
        std::stringstream str;
        while (count!=counter) //lenght 
        {
            fileIn.read(&sym, 1);
        
            /*
            if (count % 16 == 0)
               std::cout << std::endl << "0x" << std::setw(7) << std::setfill('0') << std::hex << count / 16 << "0 ";  //hex - вывод в 16-ом виде  setw формат выводв, выравнивание
            if (count % 16 == 8)
                std::cout << ' ';*/

            
            currentByte = static_cast<int>(sym);
          
            
            currentByte = (currentByte + 256) % 256;  //избавляемся от - в значениях
            _itoa_s(currentByte, sstring, 3, 16); //перевод в hex
            if (sstring[1] == '\0') {   //этот if для доабвления 0 перед цифрой hex
                sstring[2] = sstring[1];
                sstring[1] = sstring[0];
                sstring[0] = '0';
                }
            //std::cout << sstring << std::endl;
            fileInByte += sstring;                     

           // std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(sym & 0xff) << ' ';   //static_cast приведение типов
            count++;
        }
        std::cout <<"\n"<<fileInByte << std::endl;
        //td::cout << "end\n";
        fileIn.close();
        return fileInByte;
    }

    void IDSmodule::checkFormat() {
        std::string s;
        bool isDefined = false;
        std::string format;


        for (int i = 0; i < 9; i++) {
            std::cout << "i = " << i<< "\n";
            format = formatObjects[i]->getFormat();
            std::cout << format << std::endl;
            //--------------------------------------------- SCRIPT -------------------------------------------//
            if (format== "script") {   //если скрипт, то отправляем сразу его тип. тут проблема!!!!!!!! читать нужно не в 16 сс а по обычному файл
                std::string fileInCharacters = readCharachters(0, 10);
                for (int z = 0; z < 5; z++) {
                    s=fileInCharacters.substr(0,((Script*)formatObjects[i])->numb_arr[z]);
                    
                    if (s == (((Script*)formatObjects[i])->arr[z])) {
                        fileInCharacters = fileInCharacters;
                        getInfo("script",i);
                        isDefined = true;
                        break;
                    }
                }
             }
            //--------------------------------------------- ICO -------------------------------------------//
            else if (format == "ico") {
                std::cout << " entered ico \n";
                fileInBytes = readFile(0, 10);
                s = fileInBytes.substr(formatObjects[i]->getMagicOffset(), formatObjects[i]->getMagicOffsetSize());
                if (s == ((Ico*)formatObjects[i])->magic1){
                    std::cout << "it's ico1 \n";
                    ((Ico*)formatObjects[i])->magic = ((Ico*)formatObjects[i])->magic1;
                    this->fileInBytes = fileInBytes;
                    getInfo(formatObjects[i]->getFormat(), i);
                    isDefined = true;
                    break;
                }
                else if( s == ((Ico*)formatObjects[i])->magic2) {
                    std::cout << "it's ico2 \n";
                    ((Ico*)formatObjects[i])->magic = ((Ico*)formatObjects[i])->magic2;
                    this->fileInBytes = fileInBytes;
                    getInfo(formatObjects[i]->getFormat(), i);
                    isDefined = true;
                    break;
                }
            }
            //--------------------------------------------- GIF -------------------------------------------//
            else if(format == "gif") {
                
                fileInBytes = readFile(0, 7); //необходимы только превые 6 байт для опредления формата.
                s = fileInBytes.substr(formatObjects[i]->getMagicOffset(), formatObjects[i]->getMagicOffsetSize());
                
                if (s == ((Gif*)formatObjects[i])->magic1) {
                    std::cout << "it's gif11 \n";
                    formatObjects[i]->magic = ((Gif*)formatObjects[i])->magic1;
                    getInfo(formatObjects[i]->format, i);
                    isDefined = true;
                    break; 
                }
                else if (s == ((Gif*)formatObjects[i])->magic2) {
                    std::cout << "it's gif12 \n";
                    formatObjects[i]->magic = ((Gif*)formatObjects[i])->magic2;
                    getInfo(formatObjects[i]->getFormat(), i);
                    isDefined = true;
                    break;
                }
                
            }
            //--------------------------------------------- TAR -------------------------------------------//
            else if (format == "tar") { // читаем только байты, которые расположены с оффсетом 257, чтобы определить, это тар или нет
                fileInBytes = readFile(257,8);
                if (fileInBytes == ((Tar*)formatObjects[i])->magic1) {
                    formatObjects[i]->magic = ((Tar*)formatObjects[i])->getMagic(1);
                    getInfo(formatObjects[i]->getFormat(), i);
                    isDefined = true;
                    break;
                }
                else if (fileInBytes == ((Tar*)formatObjects[i])->magic2) {
                    formatObjects[i]->magic = ((Tar*)formatObjects[i])->getMagic(2);
                    getInfo(formatObjects[i]->getFormat(), i);
                    isDefined = true;
                    break;
                    }
            }
            //--------------------------------------------- OTHER -------------------------------------------//
            else if (isOtherFormat(format)) {
                fileInBytes = readFile(0, 10);  //поменять кусок кода
                s = fileInBytes.substr(formatObjects[i]->getMagicOffset(), formatObjects[i]->getMagicOffsetSize());

                 if (s == formatObjects[i]->getMagic()) {
                     getInfo(formatObjects[i]->getFormat(), i);  
                     isDefined = true;
                     break;
                 }
            }
            
            
        }
        //--------------------------------------------- UNDEFINED -------------------------------------------//
       // if (isDefined == false) {
          //  getInfo("undefined", 10); //10 это позиция члена массива  formatObjects, который является объектом undefined
       // }
    }

     void IDSmodule::getInfo(std::string format, int pointer) { 
        
        this->file = File(format, formatObjects[pointer]->getMagic()); //создали объект  (инициализировали)
        this->file.getNameAndExt(filePath);
       // this->file.fileInBytes = &this->fileInBytes;
        //std::cout << *this->file.fileInBytes;//!!!!!!!!

        std::cout << "\n" << "lenght IDS   " << this->lenght<<"\n";
        this->file.size = this->lenght;
        File* ptr = &this->file;  // создали указатель, чтобы функция parseFile изменяла созданный нами экземпляр класса File, которые является полем класса IDSmodule !!!!ptr не нужен ведь

        if (format == "zip") {
            long double startOfEODR;
            long double start_pos = (lenght - 50);
            fileInBytes = readFile(start_pos, 50);  //с запасом, посколько неизвестна длина комментария в конце файла, т.к она может быть любой :(
            startOfEODR=((Zip*)formatObjects[pointer])->findEOCDR(fileInBytes);
            std::cout << start_pos<< "  "<<startOfEODR;
            start_pos += startOfEODR/2;
            if (startOfEODR == 0) {
                std::cout << "ERROR";
            }
            else {
                fileInBytes = readFile(start_pos, 22);
                formatObjects[pointer]->parseFile(fileInBytes, ptr);
            }


        }

        if (format == "gzip") {
            fileInBytes = readFile(0,10)+readFile(lenght - 8, 8);
            formatObjects[pointer]->parseFile(this->fileInBytes, ptr);
            
        }

        if (format == "tar") {
            std::cout << "tar parse";
            formatObjects[pointer]->parseFile(fileInBytes, ptr);
        }

        if (format == "ico") {
            formatObjects[pointer]->parseFile(this->fileInBytes, ptr);

        }

        if (format == "gif") {
            formatObjects[pointer]->parseFile(this->fileInBytes, ptr);
        }

        if (format == "uimage") {
            fileInBytes = readFile(0, 32);
            formatObjects[pointer]->parseFile(fileInBytes, ptr);
        }

        if (format == "squashfs") {
            fileInBytes = readFile(0, 22);
            formatObjects[pointer]->parseFile(fileInBytes, ptr);
        }

        if (format == "elf") {

        }

        if (format == "pe") {
            fileInBytes = readFile(60, 4); //выделяем значени смещения для заголовка ПЕ
            int offset=((Pe*)formatObjects[pointer])->getPeHeader(fileInBytes);
            //pe_header
            fileInBytes = readFile(offset, 26);//узнаём время, разрядность, кол. секций
            offset += 24;
            formatObjects[pointer]->parseFile(fileInBytes, ptr);
            ((Pe*)formatObjects[pointer])->getArchBit(fileInBytes);
            //pe_opt_header
            fileInBytes = readFile(offset, ((Pe*)formatObjects[pointer])->size_of_optional_header);
            
            ((Pe*)formatObjects[pointer])->getImageBase(fileInBytes); //in dec
            ((Pe*)formatObjects[pointer])->getSectAlig(fileInBytes);  //in dec
            ((Pe*)formatObjects[pointer])->getIDD(fileInBytes);

            file.type=((Pe*)formatObjects[pointer])->getType(fileInBytes);
            file.chsum = ((Pe*)formatObjects[pointer])->getChsum(fileInBytes);


        }

        if (format == "script") {
            formatObjects[pointer]->parseFile(this->fileInBytes, ptr);
            
        }

        if (format == "undefined") {
            //возможно анализ одержимого чтобы определить тип файла... но пока оставм так.
        }
    }
     

     std::string IDSmodule::readCharachters(int start_pos, int counter) {
         std::ifstream fileIn(this->filePath, std::ios::in);
         if (!fileIn.is_open())
         {
             std::cout << "Can not open file \"" << '\"' << std::endl;
             return "Error";
         }

         std::string s;

         fileIn.seekg(0, fileIn.end);
         long double lenght = fileIn.tellg();
         this->lenght = lenght;
         //курсор в начало файла 
         fileIn.seekg(start_pos, fileIn.beg);
         int i = 0;
         char c;

         //char* buffer = new char[counter+1];
         while (i != counter) {
             fileIn.read(&c, 1);
             i++;

             s += c;
         }
         return s;
     }

     