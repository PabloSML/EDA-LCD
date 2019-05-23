#pragma once
#include "genericEventGenerator.h"
#include <curses/curses.h>
#include <iostream>
using namespace std;

enum class KB_ST { KB_OK, Init_fail };

class keyboardEvents :
	public genericEventGenerator
{
public:
	keyboardEvents();
	~keyboardEvents();
	virtual EventType getEvent(char tecla);
	virtual bool hayEvent(void);
	bool SuccessInit(void);
private:
	WINDOW * winTest;
	KB_ST status;
};
