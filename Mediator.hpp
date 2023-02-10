#pragma once

#include <stdint.h>
#include <vector>
#include "MyTools.h"
#include "Plane.h"

class Planetrack;

class Mediator{
private:
    std::vector<Planetrack*> plans;
public:
    void AddPlane(Planetrack* pNewPlane){
        plans.push_back(pNewPlane);
    }
    std::vector<Planetrack*>& getVecPlanes(){ return plans; }
};