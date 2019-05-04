#ifndef HITACHIHD44780DRIVER_H
#define HITACHIHD44780DRIVER_H

#include<cstdio>
#include<windows.h>
#include <chrono>
#define FTD2XX_EXPORTS
#include "ftd2xx.h"

#define MY_LCD_DESCRIPTION ("EDA LCD 2 B") // CAMBIAR LA DESCRIPCION SEGUN EL GRUPO
#define CONNECTING_TIME (5) //in seconds
#define ASYNCHRONOUS_BIT_BANG (1)
#define ALL_PINS_OUTPUT (0Xff)

FT_HANDLE* lcdInit();
FT_STATUS lcdDeinit(FT_HANDLE * deviceHandler);
void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor);
void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor);
void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value);
void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE rs);

#endif