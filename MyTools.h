#pragma once

#include <stdint.h>
#include <string>

namespace MyTools {

    // ������� ������ �� 0 �� 15
    enum ConsoleColor{
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };

	//=============================================================================================

    class ScreenSingleton{
    private:
        static ScreenSingleton* ScreenSingletonPtr;
        ScreenSingleton();
        ~ScreenSingleton();
        ScreenSingleton(const ScreenSingleton& root) = delete;
        ScreenSingleton& operator=(const ScreenSingleton& root) = delete;
    public:
        static ScreenSingleton* getInstance();
        void ClrScr() const;
        void __fastcall GotoXY(double x, double y);
        uint16_t GetMaxX() const;
        uint16_t GetMaxY() const;
        void SetColor(ConsoleColor color);
    };
	//=============================================================================================

    class interfaceFile{
    public:
        virtual void __fastcall OpenLogFile(const std::string& FN) = 0;
        virtual void CloseLogFile() = 0;
        virtual void __fastcall WriteToLog(const std::string& str) = 0;
        virtual void __fastcall WriteToLog(const std::string& str, int n) = 0;
        virtual void __fastcall WriteToLog(const std::string& str, double d) = 0;
    };

    //=============================================================================================
    class logFile : public interfaceFile{
    private:
        static logFile* logFilePtr;
        logFile();
        ~logFile();
        logFile(const logFile& root) = delete;
        logFile& operator=(const logFile& root) = delete;
    public:
        static logFile* getInstance();
        void __fastcall OpenLogFile(const std::string& FN);
        void CloseLogFile();
        void __fastcall WriteToLog(const std::string& str);
        void __fastcall WriteToLog(const std::string& str, int n);
        void __fastcall WriteToLog(const std::string& str, double d);
    };
	//=============================================================================================

    class LoggerSingleton : public interfaceFile{
    private:
        size_t count;
        static LoggerSingleton* LoggerSingletonPtr;
        logFile* file;
        LoggerSingleton();       
        ~LoggerSingleton();
        LoggerSingleton(const LoggerSingleton& root) = delete;
        LoggerSingleton& operator=(const LoggerSingleton& root) = delete;
    public:
        static LoggerSingleton* getInstance(logFile* _file);
        void __fastcall OpenLogFile(const std::string& FN) override;
        void CloseLogFile() override;
        void __fastcall WriteToLog(const std::string& str) override;
        void __fastcall WriteToLog(const std::string& str, int n) override;
        void __fastcall WriteToLog(const std::string& str, double d) override;
    };
};