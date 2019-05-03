#include "basicLCD.h"

basicLCD::basicLCD()
{
	//lcdInfo.lcdHandler = lcdInit(status);  // no hace falta pasarle el numero de lcd. Pasa status por referencia para el initOk
	cadd = 1;
}

basicLCD::~basicLCD()
{
	lcdInfo.lcdHandler = nullptr;
}

void basicLCD::lcdUpdateCursor()
{

}