#include "Bomb.h"

#include <iostream>
#include <algorithm>
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

void Bomb::addObserver(IObserver* obs){
    observers.push_back(obs);
}

void Bomb::eraseObserver(IObserver* obs){
    auto it = std::find(observers.begin(), observers.end(), obs);
    observers.erase(it);
}

void Bomb::update(){

}
