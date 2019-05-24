#pragma once
#include "genericDispatcher.h"

class downloadDispatcher :
	public genericDispatcher
{
public:
	downloadDispatcher();
	~downloadDispatcher();

	virtual void dispatcher(eventClass*,keyboardEvents*, networkingEvents*, timerEvents*, twitterEvents*);
};

