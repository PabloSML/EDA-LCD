#include "keyboardEvents.h"



keyboardEvents::keyboardEvents()
{
	WINDOW * winTest = NULL;    //Variable en dónde se guarda la terminal (Window) en donde voy a trabajar.
	winTest = initscr();	//inicializo screen
	if (winTest == NULL)
	{
		cout << "Couldn't initialize screen for input keyboard" << endl;
		status = KB_ST::Init_fail;
	}
	else
	{
		status = KB_ST::KB_OK;
		nodelay(winTest, TRUE); //con esta funcion configuro que getch() no sea bloqueante
	}
}


keyboardEvents::~keyboardEvents()
{
}

eventClass
keyboardEvents::getEvent(char tecla)
{
	eventClass = 
	switch (tecla)
	{

	}

	
}

bool
keyboardEvents::hayEvent(void)
{//tengo que llamar a getEvent si alguien presiono una tecla
	char i = getch(); //getch() devuelve ERR si no se presiono una tecla
	if (i != ERR) 
	{
		getEvent(i);

	}
	else
	{
		return false;	//SOLO PARA QUE COMPILE
	}
}

bool
keyboardEvents::SuccessInit(void)
{
	if (status == KB_ST::KB_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}