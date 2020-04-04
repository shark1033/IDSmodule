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
        this->db = DataBase(dbPath);
        this->filePath = filePath;
    };


    IDSmodule::~IDSmodule() {};


   



    std::string IDSmodule::readFile(int start_pos, int counter) {
        std::ifstream fileIn(this->filePath, std::ios::in | std::ios::binary);
 
        if (!fileIn.is_open())
        {
            std::cout << "Can not open file \"" << '\"' << std::endl;
            return "Error";
        }
        //����� �����
        fileIn.seekg(0, fileIn.end);
        long double lenght = fileIn.tellg();
        //������ � ������ ����� 
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
               std::cout << std::endl << "0x" << std::setw(7) << std::setfill('0') << std::hex << count / 16 << "0 ";  //hex - ����� � 16-�� ����  setw ������ ������, ������������
            if (count % 16 == 8)
                std::cout << ' ';*/

            
            currentByte = static_cast<int>(sym);
          
            
            currentByte = (currentByte + 256) % 256;  //����������� �� - � ���������
            _itoa_s(currentByte, sstring, 3, 16); //������� � hex
            if (sstring[1] == '\0') {   //���� if ��� ���������� 0 ����� ������ hex
                sstring[2] = sstring[1];
                sstring[1] = sstring[0];
                sstring[0] = '0';
                }
            //std::cout << sstring << std::endl;
            fileInByte += sstring;                     

           // std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(sym & 0xff) << ' ';   //static_cast ���������� �����
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
        

        for (int i = 0; i < 8; i++) {
            std::cout << "i = " << i<< "\n";

            //--------------------------------------------- SCRIPT -------------------------------------------//
            if (formatObjects[i]->getFormat() == "script") {   //���� ������, �� ���������� ����� ��� ���. ��� ��������!!!!!!!! ������ ����� �� � 16 �� � �� �������� ����
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
            else if (formatObjects[i]->getFormat() == "ico") {
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
            else if(formatObjects[i]->getFormat() == "gif") {
                
                fileInBytes = readFile(0, 12);
                s = fileInBytes.substr(formatObjects[i]->getMagicOffset(), formatObjects[i]->getMagicOffsetSize());
                
                if (s == ((Gif*)formatObjects[i])->magic1) {
                    std::cout << "it's gif11 \n";
                    formatObjects[i]->magic = ((Gif*)formatObjects[i])->getMagic(1);
                    getInfo(formatObjects[i]->format, i);
                    isDefined = true;
                    break; 
                }
                else if (s == ((Gif*)formatObjects[i])->magic2) {
                    std::cout << "it's gif12 \n";
                    formatObjects[i]->magic = ((Gif*)formatObjects[i])->getMagic(2);
                    getInfo(formatObjects[i]->getFormat(), i);
                    isDefined = true;
                    break;
                }
                
            }
            //--------------------------------------------- TAR -------------------------------------------//
            else if (formatObjects[i]->getFormat() == "tar") { // ������ ������ �����, ������� ����������� � �������� 257, ����� ����������, ��� ��� ��� ���
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
            fileInBytes = readFile(0, 10);
            s = fileInBytes.substr(formatObjects[i]->getMagicOffset(), formatObjects[i]->getMagicOffsetSize());

            if (s == formatObjects[i]->getMagic()) {
                getInfo(formatObjects[i]->getFormat(), i);  
                isDefined = true;
                break;
            }
            
        }
        //--------------------------------------------- UNDEFINED -------------------------------------------//
       // if (isDefined == false) {
          //  getInfo("undefined", 10); //10 ��� ������� ����� �������  formatObjects, ������� �������� �������� undefined
       // }
    }

     void IDSmodule::getInfo(std::string format, int pointer) { 
        
        this->file = File(format, formatObjects[pointer]->getMagic()); //������� ������  (����������������)
        this->file.getNameAndExt(filePath);

        std::cout << "\n" << "lenght IDS   " << this->lenght<<"\n";
        this->file.uncompressed_size = this->lenght;
        File* ptr = &this->file;  // ������� ���������, ����� ������� parseFile �������� ��������� ���� ��������� ������ File, ������� �������� ����� ������ IDSmodule !!!!ptr �� ����� ����

        if (format == "zip") {
            long double startOfEODR;
            long double start_pos = (lenght - 50);
            fileInBytes = readFile(start_pos, 50);  //� �������, ��������� ���������� ����� ����������� � ����� �����, �.� ��� ����� ���� ����� :(
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

        }
        if (format == "script") {
            formatObjects[pointer]->parseFile(this->fileInBytes, ptr);
            
        }

        if (format == "undefined") {
            //�������� ������ ���������� ����� ���������� ��� �����... �� ���� ������ ���.
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
         //������ � ������ ����� 
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

     