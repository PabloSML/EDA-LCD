#include <iostream>
#include <cctype>
#include "HitachiHD44780.h"
using namespace std;

// Ir descomentando a medida que se hacen


HitachiHD44780::HitachiHD44780() : basicLCD()
{
	if (FT_GetStatus(lcdHandler, &dump, &dump, &dump) == FT_OK)
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
	return FT_SUCCESS(FT_GetStatus(lcdHandler, &dump, &dump, &dump));
}
FT_STATUS HitachiHD44780::lcdGetError()
{
	return FT_GetStatus(lcdHandler, &dump, &dump, &dump);
}

bool HitachiHD44780::lcdClear()
{
	bool clearSuccess = false;
	lcdWriteIR(&lcdHandler, LCD_CLEAR);
	cadd = 1;
	if (FT_GetStatus(lcdHandler, &dump, &dump, &dump) == FT_OK)
	{
		cout << "LCD Clear successful" << endl;
		clearSuccess = true;
	}
	else
		cout << "LCD Clear fail" << endl;

	return clearSuccess;
}

bool HitachiHD44780::lcdClearToEOL()
{
	int cadd_backUp = this->cadd;
	int end_current_Line = this->cadd < FIRST_SEC_LINE ? END_FIRST_LINE : END_SECOND_LINE; //modificar define

	while (this->cadd <= end_current_Line  && FT_GetStatus(lcdHandler, &dump, &dump, &dump) == FT_OK)
		*this << ' ';

	this->cadd = cadd_backUp;	//recupero estado original del cursor

	return FT_SUCCESS(FT_GetStatus(lcdHandler, &dump, &dump, &dump));
}

basicLCD& HitachiHD44780::operator<<(const unsigned char c)
{
	if (isalnum(c))
	{
		lcdWriteDR(&lcdHandler, c);
		if (++cadd > END_SECOND_LINE) { cadd = HOME; }	//ni idea el nombre de los define
		lcdUpdateCursor();
	}
	return *this;
}

basicLCD& HitachiHD44780::operator<<(const unsigned char* c)
{
	int index = 0;
	int length = 0;

	while (c[index] != NULL)
		length++;

	if (length > LONG_MAX_DISPLAY)	//si excede la cantidad maxima de caracteres que puede mostrar fisicamente el display
		index = length - LONG_MAX_DISPLAY; //solo se muestran los ultimos LONG_MAX_DISPLAY caracteres

	while (c[index] != NULL)
	{
		*this << c[index]; 
	}
	//el cursor ya queda actualizado
	return *this;
}

/*
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