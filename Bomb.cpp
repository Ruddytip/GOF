
#include <iostream>

#include "Bomb.h"
#include "MyTools.h"

void Bomb::Draw() const {
    MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
    scr->SetColor(MyTools::CC_LightMagenta);
    scr->GotoXY(x, y);
    std::cout << "*";
}

void __fastcall Bomb::Accept(Visitor &v){
    v.log(this);
}
