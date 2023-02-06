#pragma once
#include <string>
#include "MyTools.h"

class Bomb;
class Plane;

class Visitor{
public:
    virtual void log(const Bomb* e) = 0;
    virtual void log(const Plane* e) = 0;
};

class LogVisitor : public Visitor{
public:
    void log(const Bomb* e) override {
        std::string out = std::string(__FUNCTION__) + " 'Bomb' was invoked";

        // out+= ", X: " +  std::to_string(e->GetX());
        // out+= ", Y: " +  std::to_string(e->GetY());
        // out+= ", Width: " +  std::to_string(e->GetWidth());
        // out+= ", Dirction: " +  std::to_string(e->GetDirection());
        // out+= ", Speed: " +  std::to_string(e->GetSpeed());

        MyTools::logFile::getInstance()->WriteToLog(out);
    }
    void log(const Plane* e) override {
        std::string out = std::string(__FUNCTION__) + " 'Plane' was invoked";

        // out+= ", X: " +  std::to_string(e->GetX());
        // out+= ", Y: " +  std::to_string(e->GetY());
        // out+= ", Width: " +  std::to_string(e->GetWidth());
        // out+= ", Dirction: " +  std::to_string(e->GetDirection());
        // out+= ", Speed: " +  std::to_string(e->GetSpeed());

        MyTools::logFile::getInstance()->WriteToLog(out);
    }
};
