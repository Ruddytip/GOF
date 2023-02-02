#pragma once

#include <stdint.h>
#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject{
public:
	bool __fastcall isInside(double x1, double x2) const override;
	inline uint16_t GetScore() const override { return score; }
	virtual void Draw() const override;
	char look[7][14];
	House(){
		for(auto i = 0; i < 7; ++i)
			for(auto j = 0; j < 14; ++j)
				look[i][j] = ' ';
	}
private:
	const uint16_t score = 40;
};

class HouseBuilder{
protected:
	House* _pHouse;
public:
	HouseBuilder() : _pHouse(nullptr) {};
	virtual ~HouseBuilder(){}
	virtual void createHouse() {}
    virtual void buildWall() {}
    virtual void buildRoof() {}
    virtual void buildWindow() {}
    virtual void buildPipe() {}
    virtual House* getHouse() { return _pHouse; }
};

class HouseBuilderA : public HouseBuilder{
public:
	virtual ~HouseBuilderA(){}
	void createHouse() override { _pHouse = new House; }
	void buildWall() override {
		for(auto i = 0; i < 14; ++i){
			_pHouse->look[3][i] = '#';
			_pHouse->look[6][i] = '#';
		}
		_pHouse->look[4][0]  = '#';
		_pHouse->look[4][13] = '#';
		_pHouse->look[5][0]  = '#';
		_pHouse->look[5][13] = '#';
	}
    void buildRoof() override {
		for(auto i = 2; i < 12; ++i) _pHouse->look[1][i] = '=';
		_pHouse->look[2][0]  = '='; _pHouse->look[2][1]  = '=';
		_pHouse->look[2][12] = '='; _pHouse->look[2][13] = '=';
	}
    void buildWindow() override {
		_pHouse->look[4][6] = '+'; _pHouse->look[4][7] = '+';
		_pHouse->look[5][6] = '+'; _pHouse->look[5][7] = '+';
	}
    void buildPipe() override { _pHouse->look[0][7] = '^'; }
};

class HouseDirector{
public:
	House* createHouse(HouseBuilder& builder){
		builder.createHouse();
		builder.buildWall();
		builder.buildRoof();
		builder.buildWindow();
		builder.buildPipe();
		return (builder.getHouse());
	}
}; 