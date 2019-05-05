#include "HitachiHD44780Driver.h"



FT_HANDLE* lcdInit(void)
{
	FT_STATUS status = !FT_OK;
	FT_HANDLE* lcdHandle = new FT_HANDLE;

	std::chrono::seconds MaxTime(CONNECTING_TIME);
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> current = start;

	while (status != FT_OK && ((current - start) < MaxTime))//loop till succesful connection o max connecting time is exceeded
	{
		status = FT_OpenEx((void *)MY_LCD_DESCRIPTION, FT_OPEN_BY_DESCRIPTION, lcdHandle);

		if (status == FT_OK)
		{
			UCHAR Mask = ALL_PINS_OUTPUT;	//Selects all FTDI pins.
			UCHAR Mode = ASYNCHRONOUS_BIT_BANG; 	// Set asynchronous bit-bang mode
			if (FT_SetBitMode(*lcdHandle, Mask, Mode) == FT_OK)
			{
				Sleep(15);
				lcdWriteNibble(lcdHandle, LCD_FUNCTION_SET_8B_2L_5X8_HIGH_NIBBLE | LCD_RS_LOW);
				Sleep(5);
				printf("iniciando:se envio el comando %x al lcd\n", LCD_FUNCTION_SET_8B_2L_5X8_HIGH_NIBBLE | LCD_RS_LOW); //solo para imprimir valor,DEBBUG BORRAR DESPUES
				lcdWriteNibble(lcdHandle, LCD_FUNCTION_SET_8B_2L_5X8_HIGH_NIBBLE | LCD_RS_LOW);
				Sleep(1);
				printf("iniciando:se envio el comando %x al lcd\n", LCD_FUNCTION_SET_8B_2L_5X8_HIGH_NIBBLE | LCD_RS_LOW); //solo para imprimir valor,DEBBUG BORRAR DESPUES
				lcdWriteNibble(lcdHandle, LCD_FUNCTION_SET_8B_2L_5X8_HIGH_NIBBLE | LCD_RS_LOW);
				Sleep(1);
				printf("iniciando:se envio el comando %x al lcd\n", LCD_FUNCTION_SET_8B_2L_5X8_HIGH_NIBBLE | LCD_RS_LOW); //solo para imprimir valor,DEBBUG BORRAR DESPUES
				lcdWriteNibble(lcdHandle, LCD_FUNCTION_SET_4B_2L_5X8_HIGH_NIBBLE | LCD_RS_LOW);
				Sleep(1);
				printf("iniciando:se envio el comando %x al lcd\n", LCD_FUNCTION_SET_4B_2L_5X8_HIGH_NIBBLE | LCD_RS_LOW); //solo para imprimir valor,DEBBUG BORRAR DESPUES
				lcdWriteIR(lcdHandle, LCD_FUNCTION_SET_4B_2L_5X8);
				Sleep(1);
				printf("iniciando:se envio el comando %x al lcd\n", LCD_FUNCTION_SET_4B_2L_5X8 | LCD_RS_LOW); //solo para imprimir valor,DEBBUG BORRAR DESPUES
				lcdWriteIR(lcdHandle, LCD_DISPLAY_CONTROL_OFF);
				Sleep(1);
				printf("iniciando:se envio el comando %x al lcd\n", LCD_DISPLAY_CONTROL_OFF); //solo para imprimir valor,DEBBUG BORRAR DESPUES
				lcdWriteIR(lcdHandle, LCD_CLEAR_SCREEN);
				Sleep(10);
				printf("iniciando:se envio el comando %x al lcd\n", LCD_CLEAR_SCREEN | LCD_RS_LOW); //solo para imprimir valor,DEBBUG BORRAR DESPUES
				lcdWriteIR(lcdHandle, LCD_ENTRY_MODE_SET);
				printf("iniciando:se envio el comando %x al lcd\n", LCD_ENTRY_MODE_SET); //solo para imprimir valor,DEBBUG BORRAR DESPUES
				Sleep(100);
				lcdWriteIR(lcdHandle, LCD_CLEAR_SCREEN);
			}
		}
		else
			std::cout << "Couldn't inicializate FTDI" << std::endl;
		current = std::chrono::system_clock::now();
	}
	return lcdHandle;
}

FT_STATUS lcdDeinit(FT_HANDLE * deviceHandler)	
{
	FT_STATUS status = FT_Close(*deviceHandler);
	delete deviceHandler;
	return status;
}


void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE value)
{
	BYTE tempValue;
	printf("Escribiendo IR:se envio el comando %x al lcd\n", value); //solo para imprimir valor,DEBBUG BORRAR DESPUES
	tempValue = (value & 0xf0) | LCD_RS_LOW ;
	lcdWriteNibble(deviceHandler,tempValue);
	tempValue = ((value << 4) & 0xf0) | LCD_RS_LOW;
	lcdWriteNibble(deviceHandler, tempValue);
}

void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE value)
{
	BYTE tempValue;
	printf("Escribiendo DR:se envio el comando %x al lcd\n", value); //solo para imprimir valor,DEBBUG BORRAR DESPUES
	tempValue = (value & 0xf0) | LCD_RS_HIGH;
	lcdWriteNibble(deviceHandler, tempValue);
	tempValue = ((value << 4) & 0xf0) | LCD_RS_HIGH;
	lcdWriteNibble(deviceHandler, tempValue);
}

void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE registerSelect)
{

}

void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value)
{
	DWORD bytesWritten;
	BYTE temp;
	temp = value | LCD_EN_LOW;
	FT_Write(deviceHandler, &temp, 1, &bytesWritten);
	printf("Envio a lcd:se envio el comando %x al lcd\n", value); //solo para imprimir valor,DEBBUG BORRAR DESPUES

	temp = value | LCD_EN_HIGH;
	FT_Write(deviceHandler, &temp, 1, &bytesWritten);
	printf("Envio a lcd:se envio el comando %x al lcd\n", value); //solo para imprimir valor,DEBBUG BORRAR DESPUES

	Sleep(5);
	temp = value & (LCD_NOT_EN_HIGH);
	FT_Write(deviceHandler, &temp, 1, &bytesWritten);
	printf("Envio a lcd:se envio el comando %x al lcd\n", value); //solo para imprimir valor,DEBBUG BORRAR DESPUES
}

/*
int print2LCD(void)
{
	FT_STATUS status = !FT_OK;
	FT_HANDLE lcdHandle = nullptr;
	unsigned char info = 0x00;
	DWORD sizeSent = 0;


	std::chrono::seconds MaxTime(CONNECTING_TIME);
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> current = start;

	while (status != FT_OK && ((current - start) < MaxTime))//loop till succesful connection o max connecting time is exceeded
	{
		status = FT_OpenEx((void *)MY_LCD_DESCRIPTION, FT_OPEN_BY_DESCRIPTION, &lcdHandle);

		if (status == FT_OK)
		{
			UCHAR Mask = 0xFF;	//Selects all FTDI pins.
			UCHAR Mode = 1; 	// Set asynchronous bit-bang mode
			if (FT_SetBitMode(lcdHandle, Mask, Mode) == FT_OK)	// Sets LCD as asynch bit mode. Otherwise it doesn't work.
			{

				//Example to write 0xf0 to the display 

				//(E=0, RS=0, D4-D7=f)...
				info = 0xf0;

				//Finally executes the action "write to LCD"...
				if (FT_Write(lcdHandle, &info, 1, &sizeSent) == FT_OK)
				{
					//If success continue with the program (...)
				}
				else
					printf("Error writing to the LCD\n");
			}
			else
				printf("Couldn't configure LCD\n");

			FT_Close(lcdHandle);
		}
		current = std::chrono::system_clock::now();
	}

	if (status != FT_OK)
		printf("Couldn't open LCD\n");

	return 0;
}
*/