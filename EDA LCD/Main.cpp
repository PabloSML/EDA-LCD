#include "HitachiHD44780Driver.h" //include solo para probar el lcd,DEBBUG BORRAR DESPUES


int main()
{
	//,DEBBUG BORRAR DESPUES******************************************************
	FT_HANDLE* handle = nullptr;
	handle = lcdInit();
	Sleep(100);
	lcdWriteIR(handle, LCD_CLEAR_SCREEN);
	Sleep(100);
	lcdWriteIR(handle, 0x0e);
	lcdWriteIR(handle, LCD_RETURN_HOME);
	lcdWriteIR(handle, LCD_CLEAR_SCREEN);
	std::cout << "*******************se inicio el display*********************" << std::endl;

	lcdWriteDR(handle, 'h');
	lcdWriteDR(handle, 'o');
	lcdWriteDR(handle, 'l');
	lcdWriteDR(handle, 'a');
	lcdWriteDR(handle, 'm');
	lcdWriteDR(handle, 'u');
	lcdWriteDR(handle, 'n');
	lcdWriteDR(handle, 'd');
	lcdWriteDR(handle, 'o');
	std::cout << "se tendria que haber escrito 'hola mundo'" << std::endl;
	//,DEBBUG BORRAR DESPUES*************************************************


	std::system("pause");	//solo para ver los couts,DEBBUG BORRAR DESPUES
	FT_STATUS closing = lcdDeinit(handle);
	if (closing == FT_OK)
		std::cout << "cerro bien" << std::endl;
	else
		std::cout << "cerro mal" << std::endl;
	std::system("pause");
	return 0;
}
