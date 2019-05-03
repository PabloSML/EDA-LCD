#include "HitachiHD44780.h"

// Ir descomentando a medida que se hacen

/*
HitachiHD44780::HitachiHD44780()
{
}

HitachiHD44780::~HitachiHD44780()
{
}
*/
bool HitachiHD44780::lcdInitOk()
{
	return FT_SUCCESS(this->status) ? true : false;
}

/*
FT_STATUS HitachiHD44780::lcdGetError()
{
}

bool HitachiHD44780::lcdClear()
{

}

bool HitachiHD44780::lcdClearToEOL()
{

}

basicLCD& HitachiHD44780::operator<<(const unsigned char c)
{

}

basicLCD& HitachiHD44780::operator<<(const unsigned char* c)
{

}

bool HitachiHD44780::lcdMoveCursorUp()
{

}

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