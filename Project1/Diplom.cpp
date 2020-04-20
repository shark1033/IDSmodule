#include <iostream>
#include "IDSmodule.h"
#include "DataBase.h"




  
        
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
    IDSmodule ids = IDSmodule("s:\\testfiles\\example.elf");
    ids.checkFormat();
    ids.file.getInfo();
  


    return 0;
}
      


        
        
  
