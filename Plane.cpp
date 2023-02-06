
#include <iostream>

#include "Plane.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void Plane::Draw() const{
    MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
    scr->SetColor(CC_LightBlue);
    scr->GotoXY(x, y);
    cout << "=========>";
    scr->GotoXY(x - 2, y - 1);
    cout << "===";
    scr->GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    scr->GotoXY(x + 3, y + 1);
    cout << "////";
}

void __fastcall Plane::Accept(Visitor &v){
    v.log(this);
}
