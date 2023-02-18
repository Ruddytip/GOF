#pragma once

#include<vector>

class CollisionDetector;
class Ground;
class Plane;
class LevelGUI;
class DestroyableGroundObject;
class Bomb;
class DynamicObject;
class GameObject;

class SBomber{
private:
    CollisionDetector* coll_detect;

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

    void AnimateScrolling();
};