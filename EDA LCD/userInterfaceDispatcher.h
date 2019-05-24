#pragma once
#include "genericDispatcher.h"
#include <string>

class userInterfaceDispatcher :
	public genericDispatcher
{
public:
	userInterfaceDispatcher();
	~userInterfaceDispatcher();

	virtual void dispatcher(eventClass*, keyboardEvents*, networkingEvents*, timerEvents*, twitterEvents*);

private:

	void print(twitterEvents* twpointer,string tuitToDisplay);
	std::string tuitToShow;
	int cutIndex;
	bool hayTuit;
};

