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
	virtual bool hayEvent(void);
	virtual eventClass getEvent(void);
	bool SuccessInit(void);

private:
	bool setEvent(char input);
	WINDOW * winTest;
	KB_ST status;
};
