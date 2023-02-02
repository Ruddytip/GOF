#include "CollisionDetector.hpp"
#include "commandDeleteObj.hpp"

void CollisionDetector::CheckPlaneAndLevelGUI(const Plane* pln, const LevelGUI* lvl_GUI, bool* flag){
    if (pln->GetX() > lvl_GUI->GetFinishX()) (*flag) = true;
}

void CollisionDetector::CheckBombsAndGround(Ground* grnd,
                                            std::vector<Bomb*> vecBombs,
                                            std::vector<DynamicObject*>& vecObjD,
                                            std::vector<DestroyableGroundObject*> vecDestoyableObjects,
                                            std::vector<GameObject*>& vecObjS,
                                            int16_t* score)
{
    Ground* pGround = grnd;
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++){
        if (vecBombs[i]->GetY() >= y){
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i], vecDestoyableObjects, vecObjS, score);
            commandDeleteDynamicObj(vecBombs[i], vecObjD).Execute();
        }
    }
}

void CollisionDetector::CheckDestoyableObjects( Bomb* pBomb,
                                                std::vector<DestroyableGroundObject*> vecDestoyableObjects,
                                                std::vector<GameObject*>& vecObj,
                                                int16_t* score)
{
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++){
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2)){
            score += vecDestoyableObjects[i]->GetScore();
            commandDeleteStaticObj(vecDestoyableObjects[i], vecObj).Execute();
        }
    }
}