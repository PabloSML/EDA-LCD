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

bool
keyboardEvents::setEvent(char tecla)
{
	myEvent.setType(EventType::KB_ev);
/*
Tolower pone las teclas en minuscula.
si la tecla no tiene minuscula,tolower devuelve la misma variable sin modificacion.
*/
	switch (tolower(tecla))
	{
		case 'q': myEvent.setData((int)kbEvType::EXIT);
				  break;

		case 'r': myEvent.setData((int)kbEvType::REPEAT);
				  break;
		
		case 's': myEvent.setData((int)kbEvType::NEXT);
				  break;

		case 'a': myEvent.setData((int)kbEvType::PREVIOUS);
				  break;

		case '+': myEvent.setData((int)kbEvType::FASTER);
				  break;
		
		case '-': myEvent.setData((int)kbEvType::SLOWER);
				  break;
		default:  break;
	}
	
}

bool
keyboardEvents::hayEvent(void)
{//tengo que llamar a getEvent si alguien presiono una tecla
	char i = getch(); //getch() devuelve ERR si no se presiono una tecla
	if (i != ERR) 
	{
		setEvent(i);
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