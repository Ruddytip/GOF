#include <iostream>

#include "LevelGUI.h"
#include "MyTools.h"

#include <cstring>

using namespace std;
using namespace MyTools;

void LevelGUI::Draw() const{
    MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
    scr->SetColor(CC_White);
    scr->GotoXY(x, y);

    char* buf = new (nothrow) char[width + 1];
    if (buf == nullptr) return;

    memset(buf, '+', width);
    buf[width] = '\0';
    cout << buf;
    scr->GotoXY(x, y + height);
    cout << buf;
    delete [] buf;
    buf = nullptr;
    
    for (size_t i = size_t(y); i < height + y; i++){
        scr->GotoXY(x, (double)i);
        cout << "+";
        scr->GotoXY(x + width - 1, (double)i);
        cout << "+";
    }

    scr->GotoXY(3, 1);
    cout << "FramePerSecond: " << static_cast<int>(fps / (passedTime / 1000.0));
    scr->GotoXY(25, 1);
    cout << "PassedTime: " << static_cast<int>(passedTime / 1000.0) << " sec";
    scr->GotoXY(46, 1);
    cout << "BombsNum: " << bombsNumber;
    scr->GotoXY(62, 1);
    cout << "Score: " << score;
}

void __fastcall LevelGUI::SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew){
    passedTime = passedTimeNew;
    fps = fpsNew;
    bombsNumber = bombsNumberNew;
    score = scoreNew;
}
