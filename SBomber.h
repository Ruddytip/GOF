#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "CollisionDetector.hpp"

class SBomber{
private:
    CollisionDetector coll_detect;

    Ground* FindGround() const;
    Plane* FindPlane() const;
    LevelGUI* FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;

    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;

public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }
    void SetExitFlag(const bool flag ) { exitFlag = flag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

    // Ground* find_ground() const { return FindGround(); }
    // Plane* find_plane() const { return FindPlane(); }
    // LevelGUI* find_levelGUI() const { return FindLevelGUI(); }
    // std::vector<DestroyableGroundObject*> find_destoyableGroundObjects() const { return FindDestoyableGroundObjects(); }
    // std::vector<Bomb*> find_AllBombs() const { return FindAllBombs(); }

    // void setScore(const int16_t scr){ score = scr; }
    // int16_t getScore() const { return score; }

    // std::vector<DynamicObject*>* getVecDynamicObj(){ return &vecDynamicObj; }
    // std::vector<GameObject*>* getVecStaticObj(){ return &vecStaticObj; }
};