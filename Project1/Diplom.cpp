#include <iostream>
#include "IDSmodule.h"
#include "DataBase.h"




   

        /*
        IDSmodule ids = IDSmodule("diplom.dblite", "s:\\testfiles\\example.gz");
        ids.db.connect();
        ids.db.selectInfo();
        ids.db.disconnect();
*/
/*
        DataBase db = DataBase("diplom.dblite");
        db.connect();
        //db.createDatabases();
        db.selectInfo();
        db.disconnect();
        */
        
int main(){
    setlocale(LC_ALL, "rus");
    /*
        IDSmodule rf = IDSmodule("s:\\testfiles\\example.txt");
        std::string fileInBytes = rf.readFile(rf.filePath);
        rf.checkFormat(fileInBytes);
        rf.file.getInfo();
       // rf.db.connect();
       // rf.db.createDatabases();
        //rf.db.insertIntoTables(rf.db.prepareInsertStatement(&rf.file).c_str());
   */
       IDSmodule ids = IDSmodule("s:\\testfiles\\example1.exe");
       ids.checkFormat();
       ids.file.getInfo();
       // ids.readCharachters(10);

        return 0;

     }
      


        
        
  
