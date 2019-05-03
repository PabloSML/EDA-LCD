#include <iostream>
#include "HitachiHD44780.h"
using namespace std;

// Ir descomentando a medida que se hacen


HitachiHD44780::HitachiHD44780() : basicLCD()
{
	if (FT_GetStatus(lcdHandler, nullptr, nullptr, nullptr) == FT_OK)
		cout << "Hitachi display constructed succesfully" << endl;
	else
		cout << "There was an error constructing the Hitachi display" << endl;
}

HitachiHD44780::~HitachiHD44780()
{
	cout << "Hitachi display destroyed" << endl;
}
bool HitachiHD44780::lcdInitOk()
{
	return FT_SUCCESS(FT_GetStatus(lcdHandler, nullptr, nullptr, nullptr));
}
FT_STATUS HitachiHD44780::lcdGetError()
{
	return FT_GetStatus(lcdHandler, nullptr, nullptr, nullptr);
}

bool HitachiHD44780::lcdClear()
{
	bool clearSuccess = false;
	lcdWriteIR(lcdHandler, LCD_CLEAR);
	cadd = 1;
	if (FT_GetStatus(lcdHandler, nullptr, nullptr, nullptr) == FT_OK)
	{
		cout << "LCD Clear successful" << endl;
		clearSuccess = true;
	}
	else
		cout << "LCD Clear fail" << endl;

	return clearSuccess;
}
/*
bool HitachiHD44780::lcdClearToEOL()
{

}

basicLCD& HitachiHD44780::operator<<(const unsigned char c)
{

}

basicLCD& HitachiHD44780::operator<<(const unsigned char* c)
{

}
*/
bool HitachiHD44780::lcdMoveCursorUp()
{

}
/*
bool HitachiHD44780::lcdMoveCursorDown()
{

}

bool HitachiHD44780::lcdMoveCursorRight()
{

}

bool HitachiHD44780::lcdMoveCursorLeft()
{

}

bool HitachiHD44780::lcdSetCursorPosition(const cursorPosition pos)
{

}

cursorPosition HitachiHD44780::lcdGetCursorPosition()
{

}
*/