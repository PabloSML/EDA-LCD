#ifndef HITACHIHD44780DRIVER_H
#define HITACHIHD44780DRIVER_H

//*************************************************INCLUDES*************************************************
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <chrono>
#define FTD2XX_EXPORTS		//FTDI LIB
#include "ftd2xx.h"

//*************************************************DEFINES*************************************************

//DEFINES GENERALES
#define MY_LCD_DESCRIPTION ("EDA LCD 3 B")	//Nombre del LCD para inicializar el FTDI
#define CONNECTING_TIME (5)				//Tiempo en segundos para int3entar la conexion con el LCD
#define ASYNCHRONOUS_BIT_BANG (1)	//Modo 1 del FTDI - ver FTDI USER MANUAL
#define ALL_PINS_OUTPUT (0Xff)		//Se configuran todos los pines del FTDI como salida
#define LONG_MAX_DISPLAY (32)
#define START_FIRST_LINE (1)
#define END_FIRST_LINE	 (16)
#define FIRST_SECOND_LINE (17)
#define END_SECOND_LINE	(32)
#define LINE_LENGHT (16)
#define DDRAM_LINE_OFFSET (0x40)

//PUERTO FISICO - ASIGNACION DE PINES
#define PORT_PIN_0 (0)
#define	PORT_PIN_1 (1)
#define PORT_PIN_4 (4)
#define PORT_PIN_5 (5)
#define PORT_PIN_6 (6)
#define PORT_PIN_7 (7)
#define PORT_PIN_8 (8)

//ASIGNACION LOGICA DEL PUERTO (PIN 2 Y 3 NO CONECTTED)
#define LCD_EN  (1 << PORT_PIN_0)	//PIN 0 - LCD ENABLE
#define LCD_RS  (1 << PORT_PIN_1)	//PIN 1 - LCD REGISTER SELECT

//FUNCIONES DEL HITACHI HD44780 - ver hoja de datos
#define LCD_RS_HIGH (LCD_RS)
#define LCD_RS_LOW (LCD_RS ^ LCD_RS)
#define LCD_EN_HIGH  (LCD_EN)
#define LCD_NOT_EN_HIGH  (~LCD_EN)
#define LCD_EN_LOW  (LCD_EN ^ LCD_EN)
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
#define LCD_DISPLAY_CONTROL_ON (0x0e)
#define LCD_ENTRY_MODE_SET (0x06)

//*************************************************FUNCIONES*************************************************
FT_HANDLE* lcdInit();	//Inicia la comunicacion con el LCD  y realiza la rutina de inicio
FT_STATUS lcdDeinit(FT_HANDLE * deviceHandler);	//Destruye el handle del FTDI 
void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor);		//Administra la instruccion para enviarselo al LCD - 4 BITS MODE
void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor);		//Administra el dato para enviarselo al LCD - 4 BITS MODE
void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value);		//Envia el nibble al LCD 

//Se desestimo el uso de la funcion lcdWritebyte ya que la conexion siempre se hara con el driver FTDI, por lo tanto
//siempre se enviaran nibbles al LCD. La parte alta de las directivas en modo 8 bits se pueden resolver 
//en tiempo de compilacion con macros

#endif