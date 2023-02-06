#pragma once

#include <vector>
#include "DynamicObject.h"
#include "Visitor.hpp"
#include "Observer.hpp"

class Bomb : public DynamicObject, public IObservable{
private:
	std::vector<IObserver*> observers;
public:
	static const uint16_t BombCost = 10;
	void Draw() const override;
	void __fastcall Accept(Visitor& v);
	
	void addObserver(IObserver* obs) override;
    void eraseObserver(IObserver* obs) override;
    void update() override;
};
