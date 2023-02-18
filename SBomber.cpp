
#include <conio.h>
#include <ctime>
#include <windows.h>

#include "LevelGUI.h"
#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "TankAdapter.hpp"
#include "House.h"
#include "commandDeleteObj.hpp"
#include "commandDropBomb.hpp"
#include "BombDecorator.hpp"
#include "Visitor.hpp"
#include "Mediator.hpp"
#include "PlaneWhitshTrack.hpp"
#include "DrawPlane.hpp"
#include "CollisionDetector.hpp"

using namespace std;
using namespace MyTools;

SBomber::SBomber()
    : exitFlag(false),
    startTime(0),
    finishTime(0),
    deltaTime(0),
    passedTime(0),
    fps(0),
    bombsNumber(10),
    score(0)
{
    MyTools::logFile* LogInstance = MyTools::logFile::getInstance();
    LogInstance->WriteToLog(string(__FUNCTION__) + " was invoked");

    MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
    LevelGUI* pGUI = new LevelGUI;
    pGUI->SetParam(passedTime, fps, bombsNumber, score);
    const uint16_t maxX = scr->GetMaxX();
    const uint16_t maxY = scr->GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    vecStaticObj.push_back(pGUI);

    coll_detect = new CollisionDetector;

    Ground* pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    vecStaticObj.push_back(pGr);

    TankAdapter* pTank = new TankAdapter;
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    vecStaticObj.push_back(pTank);

    pTank = new TankAdapter;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    vecStaticObj.push_back(pTank);

    HouseDirector dir;
    HouseBuilderA A_Builder;
    House* pHouse = dir.createHouse(A_Builder);
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    vecStaticObj.push_back(pHouse);

    std::srand(std::time(0));
    int TypePlane = rand() % 2;

    Plane* p;
    switch (TypePlane){
        case 0:  p = new ColorPlane; break;
        case 1:  p = new BigPlane;   break;
        // default: p = new Plane;      break;
    }
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    vecDynamicObj.push_back(p);

    // Mediator* dispatcher = new Mediator;
    // Planetrack* plnT = &Planetrack(p, dispatcher);
    // dispatcher->AddPlane(plnT);
}

SBomber::~SBomber(){
    for (size_t i = 0; i < vecDynamicObj.size(); i++){
        if (vecDynamicObj[i] != nullptr){
            delete vecDynamicObj[i];
        }
    }
    for (size_t i = 0; i < vecStaticObj.size(); i++){
        if (vecStaticObj[i] != nullptr){
            delete vecStaticObj[i];
        }
    }

    delete coll_detect;
}

void SBomber::MoveObjects(){
    MyTools::logFile* LogInstance = MyTools::logFile::getInstance();
    LogInstance->WriteToLog(string(__FUNCTION__) + " was invoked");
    LogVisitor logVisit;
    for (size_t i = 0; i < vecDynamicObj.size(); i++){
        if (vecDynamicObj[i] != nullptr){
            vecDynamicObj[i]->Move(deltaTime);

            Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
            if(pBomb != nullptr){ logVisit.log(pBomb); continue; }

            Plane* pPlane = dynamic_cast<Plane*>(vecDynamicObj[i]);
            if(pPlane != nullptr){ logVisit.log(pPlane); continue; }
        }
    }
};

void SBomber::CheckObjects(){
    coll_detect->CheckPlaneAndLevelGUI(FindPlane(), FindLevelGUI(), &exitFlag);
    coll_detect->CheckBombsAndGround(FindGround(), FindAllBombs(), vecDynamicObj, FindDestoyableGroundObjects(), vecStaticObj, &score);
};

vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const{
    vector<DestroyableGroundObject*> vec;
    TankAdapter* pTank;
    House* pHouse;
    for (size_t i = 0; i < vecStaticObj.size(); i++){
        pTank = dynamic_cast<TankAdapter*>(vecStaticObj[i]);
        if (pTank != nullptr){
            vec.push_back(pTank);
            continue;
        }
        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
        if (pHouse != nullptr){
            vec.push_back(pHouse);
            continue;
        }
    }
    return vec;
}

Ground* SBomber::FindGround() const{
    Ground* pGround;
    for (size_t i = 0; i < vecStaticObj.size(); i++){
        pGround = dynamic_cast<Ground *>(vecStaticObj[i]);
        if (pGround != nullptr){
            return pGround;
        }
    }
    return nullptr;
}

#include "BombIterator.hpp"

vector<Bomb*> SBomber::FindAllBombs() const{
    vector<Bomb*> vecBombs;
    BombIterator it(vecDynamicObj);
    for (; it != it.end() ; ++it){
        Bomb* pBomb = dynamic_cast<Bomb*>(*it);
        if (pBomb != nullptr) vecBombs.push_back(pBomb);
    }
    return vecBombs;
}

Plane* SBomber::FindPlane() const{
    for (size_t i = 0; i < vecDynamicObj.size(); i++){
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if (p != nullptr){
            return p;
        }
    }
    return nullptr;
}

LevelGUI* SBomber::FindLevelGUI() const{
    for (size_t i = 0; i < vecStaticObj.size(); i++){
        LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
        if (p != nullptr){
            return p;
        }
    }
    return nullptr;
}

void SBomber::ProcessKBHit(){
    int c = _getch();

    if (c == 224){
        c = _getch();
    }

    MyTools::logFile* LogInstance = MyTools::logFile::getInstance();
    LogInstance->WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c){

    case 27: // esc
        exitFlag = true;
        break;

    case 72: // up
        FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
        commandDropBomb(FindPlane(), vecDynamicObj, &bombsNumber, &score).Execute();
        // commandDropBombDecorator(FindPlane(), vecDynamicObj, &bombsNumber, &score).Execute();
        break;

    case 'B':
        // commandDropBomb(FindPlane(), vecDynamicObj, &bombsNumber, &score, 3, SMALL_CRATER_SIZE).Execute();
        commandDropBombDecorator(FindPlane(), vecDynamicObj, &bombsNumber, &score, 3, SMALL_CRATER_SIZE).Execute();
        break;

    default:
        break;
    }
}

#include "LogFileRAII.hpp"

void SBomber::DrawFrame(){
    // MyTools::logFile* LogInstance = MyTools::logFile::getInstance();
    // LogInstance->WriteToLog(std::string(__FUNCTION__) + " was invoked");
    LogFileRAII log_RAII("log_RAII.txt");
    log_RAII.getFile() << std::string(__FUNCTION__) + " was invoked" << std::endl;

    for (size_t i = 0; i < vecDynamicObj.size(); i++){
        if (vecDynamicObj[i] != nullptr){
            vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++){
        if (vecStaticObj[i] != nullptr){
            vecStaticObj[i]->Draw();
        }
    }

    MyTools::ScreenSingleton::getInstance()->GotoXY(0, 0);
    fps++;

    FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}

void SBomber::TimeStart(){
    MyTools::logFile* LogInstance = MyTools::logFile::getInstance();
    LogInstance->WriteToLog(string(__FUNCTION__) + " was invoked");
    startTime = GetTickCount();
}

void SBomber::TimeFinish(){
    finishTime = GetTickCount();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;

    MyTools::logFile* LogInstance = MyTools::logFile::getInstance();
    LogInstance->WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
}

static const size_t ScrollHeight = 30;
static const size_t ScrollWidth = 20;
static const char* ppScroll[ScrollHeight] ={"   Project manager: ",
                                            "   Ivan Vasilevich  ",
                                            "                    ",
                                            "     Developers:    ",
                                            "   Nikolay Gavrilov ",
                                            " Dmitriy Sidelnikov ",
                                            "      Eva Brown     ",
                                            "                    ",
                                            "      Designers:    ",
                                            "   Anna Pachenkova  ",
                                            "    Elena Shvaiber  ",
                                            "                    ",
                                            "                    ",
                                            "                    ",
                                            "                    ",
                                            "                    ",
                                            "                    ",
                                            "                    ",
                                            "                    ",
                                            "        test        ",
                                            "                    ",
                                            "                    ",
                                            "                    ",
                                            "                    ",
                                            "                    ",
                                            "                    ",
                                            "                    ",
                                            "        test        ",
                                            "                    ",                                            
                                            "  _______END_______ "};

void SBomber::AnimateScrolling(){
    MyTools::logFile::getInstance()->WriteToLog(string(__FUNCTION__) + " was invoked");
    auto scr = MyTools::ScreenSingleton::getInstance();
    const size_t startX = scr->GetMaxX() / 2 - ScrollWidth / 2;
    const size_t startY = scr->GetMaxY() + 1;
    double curPos = 0;
    system("color 07");

    do {
        TimeStart();
        scr->ClrScr();

        for(auto i = 0; i < ScrollHeight; ++i){
            size_t y = startY + i - curPos;
            if(y > scr->GetMaxY()) continue;
            scr->GotoXY(startX, y);
            std::cout << ppScroll[i];
        }

        TimeFinish();
        curPos += deltaTime * 0.003;
        Sleep(10);
    } while (!_kbhit() && int(curPos) <= (ScrollHeight + scr->GetMaxY()));

    scr->ClrScr();
}