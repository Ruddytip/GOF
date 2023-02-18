#pragma once
#include "DestroyableGroundObject.h"
#include "TanckAdaptee.hpp"

class TankAdapter : public DestroyableGroundObject{
private:
    TankAdaptee tank;
public:
    TankAdapter(){}
    virtual ~TankAdapter(){}
    void SetPos(double nx, double ny) override { tank.SetPos(nx, ny); }
    uint16_t GetWidth() const override { return tank.GetWidth(); }
    void Draw() const override { tank.Paint(); }
    bool isInside(double x1, double x2) const override { return tank.isInRange(x1, x2); }
    inline uint16_t GetScore() const override { return tank.GetScore(); }
    inline void SetWidth(uint16_t widthN) override { tank.SetWidth(widthN); }
};