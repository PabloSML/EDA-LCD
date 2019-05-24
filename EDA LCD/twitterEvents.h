#pragma once
#include "genericEventGenerator.h"
#include <iostream>
#include <string>
#include <list>


class twitterEvents :
	public genericEventGenerator
{
public:
	twitterEvents();
	~twitterEvents();

	virtual eventClass getEvent(void);
	virtual bool hayEvent(void);

	void setTuits(std::list<std::string>);

	std::string getNextTuit();
	std::string getSameTuit();
	std::string getPreviousTuit();
	std::string getFirstTuit(void);
	std::list<std::string> getTuits(void) { return tuits; }

private:
	size_t index;
	std::list <std::string> tuits;
};

