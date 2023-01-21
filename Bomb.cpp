
#include <iostream>

#include "Bomb.h"
#include "MyTools.h"

void Bomb::Draw() const {
    MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
    // MyTools::SetColor(CC_LightMagenta);
    scr->SetColor(MyTools::CC_LightMagenta);
    // GotoXY(x, y);
    scr->GotoXY(x, y);
    std::cout << "*";
}