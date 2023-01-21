
#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h> 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>


#include "MyTools.h"

using namespace std;

namespace MyTools {

    ofstream logOut;

    //=============================================================================================

    ScreenSingleton::ScreenSingleton(){}

    ScreenSingleton::~ScreenSingleton(){ delete ScreenSingletonPtr; }

    ScreenSingleton* ScreenSingleton::getInstance(){
        if(ScreenSingletonPtr == nullptr)
            ScreenSingletonPtr = new ScreenSingleton;
        return ScreenSingletonPtr;
    }

    void ScreenSingleton::ClrScr() const{
        system("cls");
    }

    void __fastcall ScreenSingleton::GotoXY(double x, double y){
        const COORD cc = { short(x), short(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
    }

    uint16_t ScreenSingleton::GetMaxX() const{
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12)){
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)){
                return consoleInfo.srWindow.Right;
                int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
            }
        }
        return 0;
    }

    uint16_t ScreenSingleton::GetMaxY() const {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12)){
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)){
                return consoleInfo.srWindow.Bottom;
            }
        }
        return 0;
    }

    void ScreenSingleton::SetColor(ConsoleColor color){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color); // color =  (WORD)((BackgroundColor << 4) | TextColor))
    }

    ScreenSingleton* ScreenSingleton::ScreenSingletonPtr = nullptr;
    //=============================================================================================

    logFile::logFile(){}

    logFile::~logFile(){
        if (logOut.is_open()) logOut.close();
        delete logFilePtr;
    }

    logFile* logFile::getInstance(){
        if(logFilePtr == nullptr)logFilePtr = new logFile;
        return logFilePtr;
    }

    void __fastcall logFile::OpenLogFile(const string& FN){
        logOut.open(FN, ios_base::out);
    }

    void logFile::CloseLogFile(){
        if (logOut.is_open()) logOut.close();
    }

    string GetCurDateTime(){
        auto cur = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(cur);
        char buf[64] = { 0 };
        ctime_s(buf, 64, &time);
        buf[strlen(buf) - 1] = '\0';
        return string(buf);
    }

    void __fastcall logFile::WriteToLog(const string& str){
        if (logOut.is_open()) logOut << GetCurDateTime() << " - " << str << endl;
    }

    void __fastcall logFile::WriteToLog(const string& str, int n){
        if (logOut.is_open()) logOut << GetCurDateTime() << " - " << str << n << endl;
    }

    void __fastcall logFile::WriteToLog(const string& str, double d){
        if (logOut.is_open()) logOut << GetCurDateTime() << " - " << str << d << endl;
    }
    
    logFile* logFile::logFilePtr = nullptr;
    //=============================================================================================

    LoggerSingleton::LoggerSingleton() {}

    LoggerSingleton::~LoggerSingleton(){
        CloseLogFile();
        delete LoggerSingletonPtr;
    }

    LoggerSingleton* LoggerSingleton::getInstance(logFile* _file){
        if(LoggerSingletonPtr == nullptr){
            LoggerSingletonPtr = new LoggerSingleton;
            LoggerSingletonPtr->count = 0;
            LoggerSingletonPtr->file = _file;
        }
        return LoggerSingletonPtr;
    }

    void __fastcall LoggerSingleton::OpenLogFile(const std::string& FN){
        file->OpenLogFile(FN);
    }

    void LoggerSingleton::CloseLogFile(){
        file->CloseLogFile();
    }

    void __fastcall LoggerSingleton::WriteToLog(const std::string& str){
        std::cout << count++;
        file->WriteToLog(str);
    }

    void __fastcall LoggerSingleton::WriteToLog(const std::string& str, int n){
        std::cout << count++;
        file->WriteToLog(str, n);
    }

    void __fastcall LoggerSingleton::WriteToLog(const std::string& str, double d){
        std::cout << count++;
        file->WriteToLog(str, d);
    }
    
    LoggerSingleton* LoggerSingleton::LoggerSingletonPtr = nullptr;
    //=============================================================================================

} // namespace MyTools