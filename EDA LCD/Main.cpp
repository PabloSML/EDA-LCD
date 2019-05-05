#include "basicLCD.h"
#include "HitachiHD44780.h"
#include <iostream>
using namespace std;

int main()
{
	basicLCD* basicPtr = nullptr;
	HitachiHD44780 display;
	if (display.lcdInitOk())
	{
		cout << display.lcdGetError() << endl;
		basicPtr = &display;
		cursorPosition begSec;
		begSec.column = 0;
		begSec.row = 1;
		cursorPosition midUp;
		midUp.column = 5;
		midUp.row = 0;

		*basicPtr << (const unsigned char*)"Hello World!";
		basicPtr->lcdSetCursorPosition(begSec);
		*basicPtr << (const unsigned char*)"I'm Thanos";
		system("pause");
		basicPtr->lcdClear();
		system("pause");
		*basicPtr << (const unsigned char*)"Let me show you";
		basicPtr->lcdSetCursorPosition(begSec);
		*basicPtr << (const unsigned char*)"my great power";
		system("pause");
		basicPtr->lcdClear();
		basicPtr->lcdSetCursorPosition(midUp);
		*basicPtr << (const unsigned char*)"*SNAP*";
		system("pause");
		basicPtr->lcdClear();
		*basicPtr << (const unsigned char*)"L t m  s o  y u";
		basicPtr->lcdSetCursorPosition(begSec);
		*basicPtr << (const unsigned char*)" y g ea  p we ";
		system("pause");
		basicPtr->lcdClear();


	}
	system("pause");
	return 0;
}