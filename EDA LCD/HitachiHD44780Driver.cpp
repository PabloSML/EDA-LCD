#include "HitachiHD44780Driver.h"

FT_HANDLE* lcdInit(void)
{
	FT_STATUS status = !FT_OK;
	FT_HANDLE* lcdHandle = new FT_HANDLE;

	std::chrono::seconds MaxTime(CONNECTING_TIME);
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> current = start;

	while (status != FT_OK && ((current - start) < MaxTime)) //Loop de conexion entre el FTDI y el LCD ( tiempo maximo = MaxTime)
	{
		status = FT_OpenEx((void *)MY_LCD_DESCRIPTION, FT_OPEN_BY_DESCRIPTION, lcdHandle);

		if (status == FT_OK)
		{
			UCHAR Mask = ALL_PINS_OUTPUT;	//Todos los pines del FTDI como salida
			UCHAR Mode = ASYNCHRONOUS_BIT_BANG; 	// Modo 1 de FTDI 
			if (FT_SetBitMode(*lcdHandle, Mask, Mode) == FT_OK)
			{
				//Secuencia de iniciacion
				Sleep(15);	//Demora para alcanzar la tension de funcionamiento del LCD - Hoja de Datos
				lcdWriteNibble(lcdHandle, LCD_FUNCTION_SET_8B_2L_5X8_HIGH_NIBBLE | LCD_RS_LOW);
				Sleep(5);
				lcdWriteNibble(lcdHandle, LCD_FUNCTION_SET_8B_2L_5X8_HIGH_NIBBLE | LCD_RS_LOW);
				Sleep(1);
				lcdWriteNibble(lcdHandle, LCD_FUNCTION_SET_8B_2L_5X8_HIGH_NIBBLE | LCD_RS_LOW);
				Sleep(1);
				lcdWriteNibble(lcdHandle, LCD_FUNCTION_SET_4B_2L_5X8_HIGH_NIBBLE | LCD_RS_LOW);
				Sleep(1);
				lcdWriteIR(lcdHandle, LCD_FUNCTION_SET_4B_2L_5X8);
				Sleep(1);
				lcdWriteIR(lcdHandle, LCD_DISPLAY_CONTROL_OFF);
				Sleep(1);
				lcdWriteIR(lcdHandle, LCD_CLEAR_SCREEN);
				Sleep(10);
				lcdWriteIR(lcdHandle, LCD_ENTRY_MODE_SET);

				//instruccion para prender el LCD
				lcdWriteIR(lcdHandle, LCD_DISPLAY_CONTROL_ON);
			}
		}
		else
			std::cout << "Couldn't inicializate FTDI" << std::endl;	//Mensaje de error

		current = std::chrono::system_clock::now();
	}
	return lcdHandle;
}

FT_STATUS lcdDeinit(FT_HANDLE * deviceHandler)	
{
	FT_STATUS status = FT_Close(*deviceHandler);	//apago el FTDI
	delete deviceHandler;	//Destruyo la asignacion de memoria dinamica
	return status;
}


void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE value)
{
	BYTE tempValue;
	
	tempValue = (value & 0xf0) | LCD_RS_LOW ;	//Envio la parte alta con el rs para escribir instrucciones - 4 BITS MODE
	lcdWriteNibble(deviceHandler,tempValue);	

	tempValue = ((value << 4) & 0xf0) | LCD_RS_LOW;	//Envio la parte baja con el rs para escribir instrucciones - 4 BITS MODE
	lcdWriteNibble(deviceHandler, tempValue);
}

void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE value)
{
	BYTE tempValue;
	
	tempValue = (value & 0xf0) | LCD_RS_HIGH;	//Envio la parte alta con el rs para escribir datos - 4 BITS MODE
	lcdWriteNibble(deviceHandler, tempValue);

	tempValue = ((value << 4) & 0xf0) | LCD_RS_HIGH; //Envio la parte baja con el rs para escribir datos - 4 BITS MODE
	lcdWriteNibble(deviceHandler, tempValue);
}


void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value)
{
	DWORD bytesWritten;	//variable sin uso - necesaria para FT_Write
	BYTE temp;
	//El rs ya es debidamente tratado en las funciones writeIR/writeDR
	temp = value | LCD_EN_LOW;
	FT_Write(*deviceHandler, &temp, 1, &bytesWritten);	//ENABLE =  0

	temp = value | LCD_EN_HIGH;
	FT_Write(*deviceHandler, &temp, 1, &bytesWritten); //ENABLE =  1

	Sleep(5);	//demora para que el LCD reciba correctamente el dato/instruccion
	temp = value & (LCD_NOT_EN_HIGH);
	FT_Write(*deviceHandler, &temp, 1, &bytesWritten); //ENABLE =  0
}
 