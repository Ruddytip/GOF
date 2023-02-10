#pragma once

#include "DynamicObject.h"
#include "Visitor.hpp"

class Plane : public DynamicObject {
public:
    virtual void Draw() const override;
    inline void ChangePlaneY(double dy) { yDirection += dy; }
    void __fastcall Accept(Visitor& v);
private:
};

