
#include <iostream>

#include "House.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

bool House::isInside(double x1, double x2) const{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd) return true;
	if (x1 > XBeg && x1 < XEnd) return true;
	if (x2 > XBeg && x2 < XEnd) return true;

	return false;
}

void House::Draw() const{
	MyTools::ScreenSingleton* scr = MyTools::ScreenSingleton::getInstance();
	scr->SetColor(CC_Yellow);
	for(auto i = 0; i < 7; ++i){
		scr->GotoXY(x, y - i);
		for(auto j = 0; j < 14; ++j)
		std::cout << look[6 - i][j];
	}
	// scr->GotoXY(x, y - 5);
	// cout << "  ########  ";
	// scr->GotoXY(x, y - 4);
	// cout << "##        ##";
	// scr->GotoXY(x, y - 3);
	// cout << "############";
	// scr->GotoXY(x, y - 2);
	// cout << "#          #";
	// scr->GotoXY(x, y - 1);
	// cout << "#          #";
	// scr->GotoXY(x, y);
	// cout << "############";
}