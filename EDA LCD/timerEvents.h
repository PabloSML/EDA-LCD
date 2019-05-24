#pragma once
#include "genericEventGenerator.h"
#include <chrono>
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>  // string
using namespace std::chrono;

//enum class tmEvType : int {TICK = 0};

class timerEvents :
	public genericEventGenerator
{
public:
	timerEvents();
	virtual bool hayEvent(void);
	virtual eventClass getEvent(void);

	void riseSpeed();
	void downSpeed();

	string getDate(void);

	void restartTimer(void) { origin = high_resolution_clock::now(); }

private:
	bool setEvent(void);
	high_resolution_clock::time_point origin;
	high_resolution_clock::time_point current;
	duration<double> timeSpan;
	milliseconds tick;
};

