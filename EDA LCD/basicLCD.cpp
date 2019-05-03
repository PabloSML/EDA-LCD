#include <iostream>
#include "basicLCD.h"
using namespace std;

basicLCD::basicLCD()
{
	lcdHandler = lcdInit();  // no hace falta pasarle el numero de lcd.
	cadd = 1;
	if (FT_GetStatus(lcdHandler, nullptr, nullptr, nullptr) == FT_OK)
		cout << "Basic LCD constructed successfully" << endl;
	else
		cout << "Error constructing Basic LCD" << endl;
}

basicLCD::~basicLCD()
{
	lcdHandler = lcdDeinit();
	if (FT_GetStatus(lcdHandler, nullptr, nullptr, nullptr) == FT_OK)
		cout << "Basic LCD destroyed successfully" << endl;
	else
		cout << "Error destroying Basic LCD" << endl;
	lcdHandler = nullptr;
}

void basicLCD::lcdUpdateCursor()
{

}