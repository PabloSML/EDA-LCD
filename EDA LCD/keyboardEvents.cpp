#include "keyboardEvents.h"

keyboardEvents::keyboardEvents()
{
	myEvent.setType(EventType::KB_ev);
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
		noecho();
	}
}


keyboardEvents::~keyboardEvents()
{
	endwin();
	//cout << "Keyboard destroyed succesfully" << endl;
}

bool
keyboardEvents::setEvent(char tecla)
{
	bool success = true;
	if (myEvent.isEventEmpty())
	{
		/*
		Tolower pone las teclas en minuscula.
		si la tecla no tiene minuscula,tolower devuelve la misma variable sin modificacion.
		*/
		switch (tolower(tecla))
		{
		case 'q': myEvent.setSubType((int)kbEvType::EXIT);
			break;

		case 'r': myEvent.setSubType((int)kbEvType::REPEAT);
			break;

		case 's': myEvent.setSubType((int)kbEvType::NEXT);
			break;

		case 'a': myEvent.setSubType((int)kbEvType::PREVIOUS);
			break;

		case '+': myEvent.setSubType((int)kbEvType::FASTER);
			break;

		case '-': myEvent.setSubType((int)kbEvType::SLOWER);
			break;
		default:  success = false;
			break;
		}
	}
	else
		success = false;

	return success;
}

bool
keyboardEvents::hayEvent(void)
{//tengo que llamar a getEvent si alguien presiono una tecla
	char i = getch(); //getch() devuelve ERR si no se presiono una tecla
	if (i != ERR && setEvent(i))
	{
		return true;
	}
	else
	{
		return false;
	}
}

eventClass
keyboardEvents::getEvent()
{
	eventClass temp = myEvent;
	myEvent.setSubType(NO_SUBTYPE);
	myEvent.setData(nullptr);
	return temp;
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

void
keyboardEvents::setEvent(kbEvType ev)
{
	myEvent.setSubType(ev);
}