#pragma once

#include <fstream>

class LogFileRAII{
private:
    std::ofstream _file;
public:
    LogFileRAII() = delete;
    LogFileRAII(const char* fileName){
        if(!_file.is_open()) _file.open(fileName, std::ios::app);
    }

    virtual ~LogFileRAII(){
        if(_file.is_open()) _file.close();
    }

    std::ofstream& getFile(){
        return _file;
    }
};