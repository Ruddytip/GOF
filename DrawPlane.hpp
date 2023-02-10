#pragma once
#include <iostream>
#include "Plane.h"

class DrawPlane : public Plane{
public:
    virtual void DrawBody() const  = 0;
    virtual void DrawWings() const = 0;
    virtual void DrawTail() const  = 0;
    virtual void Draw() const      = 0;
};

class ColorPlane : public DrawPlane{
public:
    virtual ~ColorPlane(){}
    void DrawBody() const override {
        MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
        scr->SetColor(MyTools::CC_LightCyan);
        scr->GotoXY(x, y);
        std::cout << "=========>";
    }
    void DrawWings() const override {
        MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
        scr->SetColor(MyTools::CC_Red);
        scr->GotoXY(x + 3, y - 1);
        std::cout << "\\\\\\\\";
        scr->GotoXY(x + 3, y + 1);
        std::cout << "////";
    }
    void DrawTail() const override {
        MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
        scr->SetColor(MyTools::CC_Yellow);
        scr->GotoXY(x - 2, y - 1);
        std::cout << "===";
    }
    void Draw() const override{
        DrawBody();
        DrawWings();
        DrawTail();
    }
};

class BigPlane : public DrawPlane{
public:
    virtual ~BigPlane(){}
    void DrawBody() const override {
        MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
        scr->SetColor(MyTools::CC_Blue);
        scr->GotoXY(x, y);
        std::cout << "=================>";
    }
    void DrawWings() const override {
        MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
        scr->SetColor(MyTools::CC_Blue);
        scr->GotoXY(x + 3, y - 1);
        std::cout << "\\\\\\\\\\";
        scr->GotoXY(x + 3, y + 1);
        std::cout << "//////";
    }
    void DrawTail() const override {
        MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
        scr->SetColor(MyTools::CC_Blue);
        scr->GotoXY(x - 2, y - 1);
        std::cout << "=====";
    }
    void Draw() const override{
        DrawBody();
        DrawWings();
        DrawTail();
    }
};