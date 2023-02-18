#pragma once
#include <stdint.h>
#include "DestroyableGroundObject.h"

class Tank : public DestroyableGroundObject{
private:
	const uint16_t score = 30;
public:
	bool __fastcall isInside(double x1, double x2) const override;
	inline uint16_t GetScore() const override { return score; }
	void Draw() const override;

	virtual ~Tank(){}

	Tank(const Tank& h){
		x = h.x;
		y = h.y;
		width = h.width;
	}

	Tank* clone() const {
		return new Tank(*this);
	}
};