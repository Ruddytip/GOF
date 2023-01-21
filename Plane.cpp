
#include <iostream>

#include "Plane.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void Plane::Draw() const{
    MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
    // MyTools::SetColor(CC_LightBlue);
    scr->SetColor(CC_LightBlue);
    // GotoXY(x, y);
    scr->GotoXY(x, y);
    cout << "=========>";
    // GotoXY(x - 2, y - 1);
    scr->GotoXY(x - 2, y - 1);
    cout << "===";
    // GotoXY(x + 3, y - 1);
    scr->GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    // GotoXY(x + 3, y + 1);
    scr->GotoXY(x + 3, y + 1);
    cout << "////";
}
