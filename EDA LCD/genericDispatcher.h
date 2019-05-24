#pragma once
#include "genericEventGenerator.h"
#include "networkingEvents.h"
#include "keyboardEvents.h"
#include "genericEventGenerator.h"
#include "timerEvents.h"
#include "twitterevents.h"
#include "eventGeneratorBundle.h"
//#include "userInterfaceDispatcher.h"
//#include "downloadDispatcher.h"


class genericDispatcher
{
public:
	virtual void dispatcher(eventClass*,keyboardEvents*, networkingEvents*, timerEvents*, twitterEvents*) = 0;
};

