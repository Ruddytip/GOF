
#include <conio.h>
#include "MyTools.h"
#include "SBomber.h"

using namespace std;

//========================================================================================================================

#include <iostream>
int main(void){
    MyTools::LoggerSingleton* log =
        MyTools::LoggerSingleton::getInstance(MyTools::logFile::getInstance());
    // MyTools::OpenLogFile("log.txt");
    log->OpenLogFile("log.txt");
    SBomber game;

    do{
        game.TimeStart();

        if (_kbhit()) game.ProcessKBHit();

        MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
        scr->ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while(!game.GetExitFlag());
    return 0;
}
