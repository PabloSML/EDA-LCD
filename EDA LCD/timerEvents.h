#pragma once
#include "genericEventGenerator.h"
#include <chrono>
using namespace std::chrono;

enum class tmEvType : int {TICK = 0};

class timerEvents :
	public genericEventGenerator
{
public:
	virtual bool hayEvent(void);
	virtual eventClass getEvent(void);

	void restartTimer(void) { origin = high_resolution_clock::now(); }

private:
	bool setEvent(void);
	high_resolution_clock::time_point origin;
	high_resolution_clock::time_point current;
	duration<double> timeSpan;
	milliseconds tick;
};

