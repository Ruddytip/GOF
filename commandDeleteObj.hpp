#pragma once
#include "command.hpp"

// void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
class commandDeleteDynamicObj : public Command{
private:
    DynamicObject* _pObj;
    std::vector<DynamicObject*>* _pVec;
public:
    commandDeleteDynamicObj() = delete;
    commandDeleteDynamicObj(DynamicObject* ptr, std::vector<DynamicObject*>& vec) : _pObj(ptr), _pVec(&vec) {}
    virtual ~commandDeleteDynamicObj() {}
    virtual void __fastcall Execute() override{
        auto it = _pVec->begin();
        for (; it != _pVec->end(); it++){
            if (*it == _pObj){
                delete _pObj;
                _pVec->erase(it);
                break;
            }
        }
    }
};

// void __fastcall DeleteStaticObj(GameObject* pObj);
class commandDeleteStaticObj : public Command{
private:
    GameObject* _pObj;
    std::vector<GameObject*>* _pVec;
public:
    commandDeleteStaticObj() = delete;
    commandDeleteStaticObj(GameObject* ptr, std::vector<GameObject*>& vec) : _pObj(ptr), _pVec(&vec) {}   
    virtual ~commandDeleteStaticObj() {}
    virtual void __fastcall Execute() override{
        auto it = _pVec->begin();
        for(; it != _pVec->end(); it++){
            if (*it == _pObj){
                delete _pObj;
                _pVec->erase(it);
                break;
            }
        }
    }
};