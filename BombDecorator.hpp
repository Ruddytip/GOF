#pragma once

#include <iostream>
#include "Bomb.h"
#include "MyTools.h"

class BombDecorator : public DynamicObject{
private:
    Bomb* _bomb;
public:
    BombDecorator() = delete;
    BombDecorator(Bomb* ptr) : _bomb(ptr) {}
    virtual ~BombDecorator() { delete _bomb; }
    virtual void Move(uint16_t time) override{
        _bomb->Move(time * 1.6);
    }

    virtual void Draw() const override{
        _bomb->Draw();
        // Некоторое изменение внешнего вида бомбы
        auto scr = MyTools::ScreenSingleton::getInstance();
        scr->GotoXY(_bomb->GetX(), _bomb->GetY() - 1);
        std::cout << "|";
    }

    void SetPos(double nx, double ny) override { _bomb->SetPos(nx, ny); }

    uint16_t GetWidth() const override { return _bomb->GetWidth(); }
};