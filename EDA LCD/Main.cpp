
/*#include <iostream>
#include <curl/curl.h>
#include "basicLCD.h"
#include "HitachiHD44780.h"
#include <iostream>
#include <exception>
#include <list>
#include <string>
#include <curses/curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "networkingEvents.h"
#include "keyboardEvents.h"
#include "genericEventGenerator.h"
#include "twitterevents.h"*/
#include "networkingEvents.h"
#include "keyboardEvents.h"
#include "timerEvents.h"
#include "eventGeneratorBundle.h"
#include "userInterfaceDispatcher.h"
#include "downloadDispatcher.h"

using namespace std;

#define ACCOUNT "lanacion"
#define TWEETSCANT 5


int main()
{

	keyboardEvents keyboard;
	networkingEvents network(ACCOUNT, TWEETSCANT);
	timerEvents timer;
	twitterEvents tuits;
	
	//eventClass evento;
	//cout << "TOKEN DE TUITER\n" << network.getToken() << endl;

	//ESTAS DOS FUNCIONES VAN CON EL OTRO DISPATCHER
	network.downloadTuits();
	tuits.setTuits(network.getDownloadTuits());

	//cout  << "syze" << tuits.getTuits().size() << endl;
	//cout << "syze" << *(tuits.getTuits().begin) << endl;
	//aSleep(10000);

	eventGeneratorBundle* eventGenerator = new eventGeneratorBundle;
	genericDispatcher* mainDispatcher = nullptr;
	downloadDispatcher* gettingTuits =  new downloadDispatcher;
	userInterfaceDispatcher* showTuits =  new userInterfaceDispatcher;

	mainDispatcher = showTuits;

	eventGenerator->attach(&keyboard);
	eventGenerator->attach(&network);
	eventGenerator->attach(&timer);
	eventGenerator->attach(&tuits);

	//basicLCD* basicPtr = nullptr;
	//HitachiHD44780 display;
	//if (display.lcdInitOk())	//inicializo lcd
	//{
		//cout << display.lcdGetError() << endl;
		//basicPtr = &display;	//puntero al display
	/*string account(ACCOUNT);
	networkingEvents mynetworking(account, TWEETSCANT);

	if (!(mynetworking.isStatusOK()))
	{
		cout << "no se pudo inicializar networking" << endl;
		system("pause");
		return 0;
	}


	// Vamos a utilizar la librería CURL ya que debemos conectarons a un servidor HTTPS
	// (HTTP seguro) el cual requeire un protocolo especial de encriptación
	// más complejo que el plain HTTP que utilizamos en el TP de Networking.


	while (mynetworking.stillRunning)
	{
		//Debemos hacer polling de la transferencia hasta que haya terminado
		curl_multi_perform(mynetworking.multiHandle, &mynetworking.stillRunning);

		//Mientras tanto podemos hacer otras cosas
	}

	mynetworking.checkError();
	if (!(mynetworking.isStatusOK()))
	{
		cout << "fallo networking" << endl;
		system("pause");
	}

	while (1)
	{

	}*/
	//cout << "Me voy a conectar" << endl;
	//networkingEvents twitter(ACCOUNT, TWEETSCANT);
	//cout << "ya obtuve los tuits" << endl;
	//cout << "voy a inicializar el teclado" << endl;
	//keyboardEvents keyboard;
	//cout << "ya inicialice el teclado" << endl;
	//eventClass evento;
	//cout << "ya inicialice el evento" << endl;
	
	while (eventGenerator->Continue())
	{
		if (eventGenerator->hayEvent())
		{
			//cout << "hubo evento" << endl;
			mainDispatcher->dispatcher(&eventGenerator->getEvent(), &keyboard, &network, &timer, &tuits);
			/*
			evento = keyboard.getEvent();
			cout << "tipo de dato: " << (int)evento.getType() << endl;
			cout << "tipo de subdato: " << evento.getSubType() << endl;
			//cout << "BOOL EVENTO TECLADO: " << (string)evento.getData() << endl;
			//Sleep(1000);
			*/
		}
	}

	//system("pause");

	delete gettingTuits;
	delete showTuits;
	
	return 0;
}

