#include "HitachiHD44780Driver.h" //include solo para probar el lcd,DEBBUG BORRAR DESPUES


int main()
{
	//,DEBBUG BORRAR DESPUES******************************************************
	FT_HANDLE* handle = nullptr;
	handle = lcdInit();
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

	return 0;
}
