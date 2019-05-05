#include "basicLCD.h"
#include "HitachiHD44780.h"
#include <iostream>
using namespace std;

int main()
{
	basicLCD* basicPtr = nullptr;
	HitachiHD44780 display;
	basicPtr = &display;
	cursorPosition begSec;
	begSec.column = 0;
	begSec.row = 1;

	*basicPtr << (const unsigned char*)"Hello World!";
	basicPtr->lcdSetCursorPosition(begSec);
	*basicPtr << (const unsigned char*)"I'm Thanos";
	system("pause");
	return 0;
}