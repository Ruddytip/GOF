#pragma once

#include "command.hpp"
#include "Plane.h"

// void DropBomb();
class commandDropBomb : public Command{
protected:
    Plane* _pPlane;
    std::vector<DynamicObject*>* _pVec;
    uint16_t* _pBombsNumber;
    int16_t* _pScore;
    double _speed;
    uint16_t _width;
public:
    commandDropBomb() = delete;
    commandDropBomb(Plane* const plane, std::vector<DynamicObject*>& vec, uint16_t* const bombsNumber, int16_t* const score);
    commandDropBomb(Plane* const plane,
                    std::vector<DynamicObject*>& vec,
                    uint16_t* const bombsNumber,
                    int16_t* const score,
                    const double speed,
                    const uint16_t width);
    virtual void __fastcall Execute() override;
};

class commandDropBombDecorator : public commandDropBomb{
public:
    commandDropBombDecorator() = delete;
    commandDropBombDecorator(Plane* const plane, std::vector<DynamicObject*>& vec, uint16_t* const bombsNumber, int16_t* const score);
    commandDropBombDecorator(Plane* const plane,
                            std::vector<DynamicObject*>& vec,
                            uint16_t* const bombsNumber,
                            int16_t* const score,
                            const double speed,
                            const uint16_t width);
    virtual void __fastcall Execute() override;
};