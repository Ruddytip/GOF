#pragma once

#include <vector>
#include "Plane.h"
#include "Mediator.hpp"

class Mediator;

class Planetrack : public Plane{
private:
    Plane* pln;
    Mediator* dis;
public:
    Planetrack(Plane* plane, Mediator* med)
    : pln(plane), dis(med) {}
    virtual ~Planetrack(){}
    // Возвращает самолёт, c которым столкнулись
    Plane* CheckTrack(){
        for(const auto& it : dis->getVecPlanes()){
            if(it->GetX() == pln->GetX()
             & it->GetY() == pln->GetY()){
                return it;
            }
        }
        return nullptr;
    }
};