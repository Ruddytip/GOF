#pragma once
#include <vector>
#include "Bomb.h"

class BombIterator{
private:
    std::vector<DynamicObject*> refArr;
    int curIndex;
public:
    BombIterator(const std::vector<DynamicObject*>& ref) : refArr(ref), curIndex(0) {}
    virtual ~BombIterator(){}
    void reset(){ curIndex = 0; }
    void setIndex(const int i){ curIndex = i; }

    BombIterator& operator++(){
        curIndex++;
        return *this;
    }

    BombIterator& operator--(){
        curIndex--;
        return *this;
    }

    DynamicObject* operator*(){ return refArr[curIndex]; }
    bool operator==(const BombIterator& it){
        if(curIndex == it.curIndex && refArr == it.refArr){
            return true;
        }
        return false;
    }
    bool operator!=(const BombIterator& it){ return !(*this == it); }

    BombIterator begin(){ return BombIterator(refArr); }

    BombIterator end(){ BombIterator it(refArr); it.setIndex(refArr.size() - 1); return it; }
};