#include "commandDropBomb.hpp"
#include "MyTools.h"
#include "Ground.h"
#include "Bomb.h"
#include "BombDecorator.hpp"

commandDropBomb::commandDropBomb(Plane* const plane, std::vector<DynamicObject*>& vec, uint16_t* const bombsNumber, int16_t* const score)
: _pPlane(plane), _pVec(&vec), _pBombsNumber(bombsNumber), _pScore(score), _speed(2), _width(SMALL_CRATER_SIZE) {}

commandDropBomb::commandDropBomb(Plane* const plane,
                std::vector<DynamicObject*>& vec,
                uint16_t* const bombsNumber,
                int16_t* const score,
                const double speed,
                const uint16_t width)
: _pPlane(plane), _pVec(&vec), _pBombsNumber(bombsNumber), _pScore(score), _speed(speed), _width(width) {}

void __fastcall commandDropBomb::Execute(){
    if (*_pBombsNumber > 0){
        MyTools::logFile* LogInstance = MyTools::logFile::getInstance();
        LogInstance->WriteToLog(std::string(__FUNCTION__) + " was invoked");
        // WriteToLog(string(__FUNCTION__) + " was invoked");
    
        double x = _pPlane->GetX() + 4;
        double y = _pPlane->GetY() + 2;

        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(_speed);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(_width);

        _pVec->push_back(pBomb);
        (*_pBombsNumber)--;
        (*_pScore) -= Bomb::BombCost;
    }
}

commandDropBombDecorator::commandDropBombDecorator(Plane* const plane, std::vector<DynamicObject*>& vec, uint16_t* const bombsNumber, int16_t* const score)
:  commandDropBomb(plane, vec, bombsNumber, score) {}

commandDropBombDecorator::commandDropBombDecorator(Plane* const plane,
                                                std::vector<DynamicObject*>& vec,
                                                uint16_t* const bombsNumber,
                                                int16_t* const score,
                                                const double speed,
                                                const uint16_t width)
:  commandDropBomb(plane, vec, bombsNumber, score, speed, width) {}

void __fastcall commandDropBombDecorator::Execute(){
    if (*_pBombsNumber > 0){
        MyTools::logFile* LogInstance = MyTools::logFile::getInstance();
        LogInstance->WriteToLog(std::string(__FUNCTION__) + " was invoked");
        // WriteToLog(string(__FUNCTION__) + " was invoked");
    
        double x = _pPlane->GetX() + 4;
        double y = _pPlane->GetY() + 2;

        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(_speed);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(_width);
        
        BombDecorator* bombDecor = new BombDecorator(pBomb);
        _pVec->push_back(bombDecor);
        (*_pBombsNumber)--;
        (*_pScore) -= Bomb::BombCost;
    }
}