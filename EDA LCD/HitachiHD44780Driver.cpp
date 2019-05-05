#include "HitachiHD44780Driver.h"



FT_HANDLE* lcdInit(void)
{
	FT_STATUS status = !FT_OK;
	FT_HANDLE lcdHandle = nullptr;

	std::chrono::seconds MaxTime(CONNECTING_TIME);
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> current = start;

	while (status != FT_OK && ((current - start) < MaxTime))//loop till succesful connection o max connecting time is exceeded
	{
		status = FT_OpenEx((void *)MY_LCD_DESCRIPTION, FT_OPEN_BY_DESCRIPTION, &lcdHandle);

		if (status == FT_OK)
		{
			UCHAR Mask = ALL_PINS_OUTPUT;	//Selects all FTDI pins.
			UCHAR Mode = ASYNCHRONOUS_BIT_BANG; 	// Set asynchronous bit-bang mode
			if (FT_SetBitMode(lcdHandle, Mask, Mode) == FT_OK)
			{
				lcdWriteIR(&lcdHandle, LCD_FUNCTION_SET_8B_2L_5X8);
				Sleep(15);
				lcdWriteIR(&lcdHandle, LCD_FUNCTION_SET_8B_2L_5X8);
				Sleep(5);
				lcdWriteIR(&lcdHandle, LCD_FUNCTION_SET_8B_2L_5X8);
				Sleep(1);
				lcdWriteNibble(&lcdHandle, LCD_FUNCTION_SET_4B_2L_5X8_HIGH_NIBBLE);
				Sleep(1);
				lcdWriteIR(&lcdHandle, LCD_FUNCTION_SET_4B_2L_5X8);
				Sleep(1);
				lcdWriteIR(&lcdHandle, LCD_DISPLAY_CONTROL_OFF);
				Sleep(1);
				lcdWriteIR(&lcdHandle, LCD_CLEAR_SCREEN);
				Sleep(1);
				lcdWriteIR(&lcdHandle, LCD_ENTRY_MODE_SET);
				Sleep(1);
			}
		}
		current = std::chrono::system_clock::now();
	}
	return &lcdHandle;
}

FT_STATUS lcdDeinit(FT_HANDLE * deviceHandler)
{
	FT_STATUS status = FT_OK;

	return status;
}


void lcdWriteIR(FT_HANDLE * deviceHandler, BYTE valor)
{

}
void lcdWriteDR(FT_HANDLE * deviceHandler, BYTE valor)
{

}

void lcdWriteByte(FT_HANDLE * deviceHandler, BYTE value, BYTE rs)
{

}

void lcdWriteNibble(FT_HANDLE * deviceHandler, BYTE value)
{
	DWORD bytesWritten;
	if (FT_Write(deviceHandler, &value, sizeof(value), &bytesWritten) == FT_OK)
	{
		std::cout << "Escritura correcta" << std::endl;
	}
	else
	{
		std::cout << "Error de escritura" << std::endl;
	}
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