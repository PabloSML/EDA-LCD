#include <iostream>
#include "basicLCD.h"
using namespace std;

basicLCD::basicLCD()
{
	lcdHandler = lcdInit();  // no hace falta pasarle el numero de lcd.
	cadd = 1;
	if (FT_GetStatus(*lcdHandler, &dump, &dump, &dump) == FT_OK)
		cout << "Basic LCD constructed successfully" << endl;
	else
		cout << "Error constructing Basic LCD" << endl;
}

basicLCD::~basicLCD()
{
	FT_STATUS closing = lcdDeinit(lcdHandler);
	if (closing == FT_OK)
		cout << "Basic LCD destroyed successfully" << endl;
	else
		cout << "Error destroying Basic LCD" << endl;
	lcdHandler = nullptr;
}

void basicLCD::lcdUpdateCursor()
{
	if (cadd <= END_FIRST_LINE)		//antes de actualizar posicion del cursor reviso en que linea estoy.
		lcdWriteIR(lcdHandler, LCD_SET_DDRAM_ADD | (cadd-1));
	else
		lcdWriteIR(lcdHandler, LCD_SET_DDRAM_ADD | DDRAM_LINE_OFFSET | ((cadd-1) % LINE_LENGHT));
}