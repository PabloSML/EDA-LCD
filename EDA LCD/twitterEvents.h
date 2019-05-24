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

	void setTuits(std::list<std::string> dloadTuits, std::list<std::string> dloadDates);
	void setEvent(TW_EV_TYPE ev);

	std::string getDate(void);
	std::string getNextTuit(void);
	std::string getSameTuit(void);
	std::string getPreviousTuit(void);
	std::string getFirstTuit(void);
	std::list<std::string> getTuits(void) { return tuits; }

private:
	size_t index;
	std::list <std::string> tuits;
	std::list <std::string> dates;
};

