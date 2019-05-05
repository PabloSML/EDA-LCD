#ifndef HITACHIHD44780DRIVER_H
#define HITACHIHD44780DRIVER_H

#include <iostream>
#include <cstdio>
#include <windows.h>
#include <chrono>
#define FTD2XX_EXPORTS
#include "ftd2xx.h"

#define MY_LCD_DESCRIPTION ("EDA LCD 3 B") // CAMBIAR LA DESCRIPCION SEGUN EL GRUPO
#define CONNECTING_TIME (5) //in seconds
#define ASYNCHRONOUS_BIT_BANG (1)
#define ALL_PINS_OUTPUT (0Xff)

#define PORT_PIN_0 (0)
#define	PORT_PIN_1 (1)
#define PORT_PIN_4 (4)
#define PORT_PIN_5 (5)
#define PORT_PIN_6 (6)
#define PORT_PIN_7 (7)
#define PORT_PIN_8 (8)

#define LCD_EN  (1 << PORT_PIN_0)
#define LCD_RS  (1 << PORT_PIN_1)

#define LCD_RS_HIGH (LCD_RS)
#define LCD_RS_LOW (LCD_RS ^ LCD_RS)
#define LCD_EN_HIGH  (LCD_EN)
#define LCD_NOT_EN_HIGH  (~LCD_EN)
#define LCD_EN_LOW  (LCD_EN ^ LCD_EN)

#define LCD_WRITE_DATA (LCD_RS_HIGH)
#define LCD_CLEAR_SCREEN (0x01)
#define LCD_SET_DDRAM_ADD (0x80)
#define LCD_CURSOR_R (0x14)
#define LCD_CURSOR_L (0x10)
#define LCD_DISPLAY_SHIFT_R (0x1B)
#define LCD_DISPLAY_SHIFT_L (0x18)
#define LCD_RETURN_HOME (0x02)
#define LCD_FUNCTION_SET_8B_2L_5X8 (0x38)
#define LCD_FUNCTION_SET_4B_2L_5X8 (0x28)
#define LCD_FUNCTION_SET_8B_2L_5X8_HIGH_NIBBLE (LCD_FUNCTION_SET_8B_2L_5X8 & 0xf0)
#define LCD_FUNCTION_SET_4B_2L_5X8_HIGH_NIBBLE (LCD_FUNCTION_SET_4B_2L_5X8 & 0xf0)
#define LCD_DISPLAY_CONTROL_OFF (0x08)
#define LCD_ENTRY_MODE_SET (0x07)

#define LONG_MAX_DISPLAY (32)
#define START_FIRST_LINE (1)
#define END_FIRST_LINE	 (16)
#define FIRST_SECOND_LINE (17)
#define END_SECOND_LINE	(32)
#define LINE_LENGHT (16)

#define DDRAM_LINE_OFFSET (0x40)





FT_HANDLE* lcdInit();
FT_STATUS lcdDeinit(FT_HANDLE * deviceHandler);
void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor);
void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor);
void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value);
void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE rs);

#endif