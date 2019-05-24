#include "timerEvents.h"
#include <iostream>

timerEvents::timerEvents() 
{
	myEvent.setType(EventType::TM_ev);
	myEvent.setSubType((int)TM_EV_TYPE::REFRESH);
	tick = (milliseconds)1000;
}

bool
timerEvents::setEvent()
{
	bool success = false;
	if (myEvent.isEventEmpty())
	{
		success = true;
	}

	return success;
}

eventClass
timerEvents::getEvent(void)
{
	return myEvent;
}

bool
timerEvents::hayEvent(void)
{
	//std::cout << "PREGUNTO POR EL EVENTO" << std::endl;
	bool isThereEvent = false;
	current = high_resolution_clock::now();
	timeSpan = duration_cast<duration<double>> (current - origin);
	if (timeSpan > tick)
	{
		//if (setEvent())
		//{
			isThereEvent = true;
	
			//std::cout << "HUBO EVENTO DE TIMER EN HAYEVENT" << std::endl;
		//}
		restartTimer();
	}

	return isThereEvent;
}

void
timerEvents::riseSpeed()
{
	
}

void
timerEvents::downSpeed()
{
		
}


std::string
timerEvents::getDate(void)
{
	/*std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	std::string s(30, '\0');
	std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
	return s;*/

	//AGREGAR FUNCION PARA OBTENER LA FECHA
	string str = "PONER FECHA";
	return str;
}