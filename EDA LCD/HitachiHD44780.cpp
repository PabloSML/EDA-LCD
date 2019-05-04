#include <iostream>
#include <cctype>
#include <cstring>
#include "HitachiHD44780.h"
using namespace std;

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
	int end_current_Line = this->cadd < FIRST_SECOND_LINE ? END_FIRST_LINE : END_SECOND_LINE; //modificar define

	while (this->cadd <= end_current_Line  && FT_GetStatus(lcdHandler, &dump, &dump, &dump) == FT_OK)
		*this << ' ';

	this->cadd = cadd_backUp;	//recupero estado original del cursor

	return FT_SUCCESS(FT_GetStatus(lcdHandler, &dump, &dump, &dump));
}

basicLCD& HitachiHD44780::operator<<(const unsigned char c)
{
	if (isprint(c))
	{
		lcdWriteDR(&lcdHandler, c);	// la funcion de write modifica automaticamente el cursor del display, solo hay que cambiar el cadd
		if (++cadd > END_SECOND_LINE) 
		{ 
			cadd = LCD_RETURN_HOME;
		}	
	}
	return *this;
}

basicLCD& HitachiHD44780::operator<<(const unsigned char* c)
{
	int index = 0;
	int length = strlen((const char*)c);

	if (length > LONG_MAX_DISPLAY)	//si excede la cantidad maxima de caracteres que puede mostrar fisicamente el display
	{
		cadd = LCD_RETURN_HOME;						//me aseguro que el cursor este en el inicio para mostrar los 32 caracteres correctamente
		lcdUpdateCursor();
		index = length - LONG_MAX_DISPLAY; //solo se muestran los ultimos 32 caracteres
	}

	for(index; index < length; index++)
	{
		*this << c[index];				//el filtrado de caracteres se hace en la sobrecarga de 1 caracter
	}
	//el cursor ya queda actualizado
	return *this;
}


bool HitachiHD44780::lcdMoveCursorUp()
{
	bool success = false;
	if (cadd > END_FIRST_LINE)
	{
		cadd -= LINE_LENGHT; // LINE_LENGHT = 16
		lcdUpdateCursor();
		success = true;
	}
	return success;
}

bool HitachiHD44780::lcdMoveCursorDown()
{
	bool success = false;
	if (cadd <= END_FIRST_LINE)
	{
		cadd += LINE_LENGHT; // LINE_LENGHT = 16
		lcdUpdateCursor();
		success = true;
	}
	return success;
}

bool HitachiHD44780::lcdMoveCursorRight()
{
	bool success = false;
	if (cadd < END_SECOND_LINE)
	{
		cadd++;
		lcdUpdateCursor();
		success = true;
	}
	return success;
}

bool HitachiHD44780::lcdMoveCursorLeft()
{
	bool success = false;
	if (cadd > START_FIRST_LINE)  // START_FIRST_LINE = 1
	{
		cadd--; 
		lcdUpdateCursor();
		success = true;
	}
	return success;
}

bool HitachiHD44780::lcdSetCursorPosition(const cursorPosition pos)	// en lo posible cambiar numeros magicos
{
	bool success = false;
	if (pos.column >= 0 && pos.column < 16 && pos.row >= 0 && pos.row < 2)
	{
		cadd = pos.row * 16 + pos.column + 1;
		lcdUpdateCursor();
		success = true;
	}
	return success;
}

cursorPosition HitachiHD44780::lcdGetCursorPosition()	// tambien estaria bueno cambiar el 16 por un define
{
	cursorPosition temp;
	temp.row = (cadd-1) / 16;
	temp.column = (cadd-1) % 16;
	return temp;
}
