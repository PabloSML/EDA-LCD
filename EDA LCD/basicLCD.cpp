#include "basicLCD.h"

basicLCD::basicLCD()
{
	//lcdHandler = lcdInit(status);  // no hace falta pasarle el numero de lcd. Pasa status por referencia para el initOk
	cadd = 1;
}

basicLCD::~basicLCD()
{
	lcdHandler = nullptr;
}

void basicLCD::lcdUpdateCursor()
{

}