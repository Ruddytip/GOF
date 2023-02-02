#include <conio.h>
#include "MyTools.h"
#include "SBomber.h"

using namespace std;

//========================================================================================================================

#include <iostream>
int main(void){
    MyTools::LoggerSingleton::getInstance(MyTools::logFile::getInstance())->OpenLogFile("log.txt");
    SBomber game;

    do{
        game.TimeStart();

        if (_kbhit()) game.ProcessKBHit();

        MyTools::ScreenSingleton::getInstance()->ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while(!game.GetExitFlag());
    return 0;
}
