#pragma once
#include <iostream>
#include "MyTools.h"

class TankAdaptee {
public:

    TankAdaptee() : x(0.0), y(0.0), width(0) { }

    TankAdaptee(const TankAdaptee& h){
        x = h.x;
        y = h.y;
        width = h.width;
    }

    virtual ~TankAdaptee(){}

    void Paint() const {
        MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
        scr->SetColor(MyTools::CC_Brown);
        scr->GotoXY(x, y - 3);
        std::cout << "    #####";
        scr->GotoXY(x - 2, y - 2);
        std::cout << "#######   #";
        scr->GotoXY(x, y - 1);
        std::cout << "    #####";
        scr->GotoXY(x, y);
        std::cout << " ###########";
    }

    bool __fastcall isInRange(double x1, double x2) const{
        const double XBeg = x + 2;
        const double XEnd = x + width - 1;
        if (x1 < XBeg && x2 > XEnd) return true;
        if (x1 > XBeg && x1 < XEnd) return true;
        if (x2 > XBeg && x2 < XEnd) return true;
        return false;
    }

    inline uint16_t GetScore() const { return score; }

    inline void SetPos(double nx, double ny) { x = nx; y = ny; }
    inline double GetY() const { return y; }
    inline double GetX() const { return x; }

    inline void SetWidth(uint16_t widthN) { width = widthN; }
    inline uint16_t GetWidth() const { return width; }

    TankAdaptee operator=(const TankAdaptee& h){
        x = h.x;
        y = h.y;
        width = h.width;
        return *this;
    }

protected:

    double x, y;
    uint16_t width;
    const uint16_t score = 30;
};