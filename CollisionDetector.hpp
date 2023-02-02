#pragma once
#include <vector>
#include "Plane.h"
#include "Ground.h"
#include "LevelGUI.h"
#include "Bomb.h"
#include "DestroyableGroundObject.h"

class CollisionDetector{
public:
    virtual ~CollisionDetector(){}
    void CheckPlaneAndLevelGUI(const Plane* pln, const LevelGUI* lvl_GUI, bool* flag);
    void CheckBombsAndGround(   Ground* grnd,
                                std::vector<Bomb*> vecBombs,
                                std::vector<DynamicObject*>& vecObjD,
                                std::vector<DestroyableGroundObject*> vecDestoyableObjects,
                                std::vector<GameObject*>& vecObjS,
                                int16_t* score);

    void __fastcall CheckDestoyableObjects( Bomb* pBomb,
                                            std::vector<DestroyableGroundObject*> vecDestoyableObjects,
                                            std::vector<GameObject*>& vecObj,
                                            int16_t* score);
};