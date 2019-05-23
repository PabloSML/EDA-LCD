
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

using namespace std;

#define ACCOUNT "lanacion"
#define TWEETSCANT 10


int main()
{
	
	//basicLCD* basicPtr = nullptr;
	//HitachiHD44780 display;
	//if (display.lcdInitOk())	//inicializo lcd
	//{
		//cout << display.lcdGetError() << endl;
		//basicPtr = &display;	//puntero al display
		
	string account(ACCOUNT);
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
		return 0;
	}

	
		return 0;

}


