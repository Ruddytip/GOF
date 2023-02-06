#pragma once

#include "DynamicObject.h"
#include "Visitor.hpp"

class Bomb : public DynamicObject{
public:
	static const uint16_t BombCost = 10;
	void Draw() const override;
	void __fastcall Accept(Visitor& v);
private:
};
