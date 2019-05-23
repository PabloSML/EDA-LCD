#pragma once
#include "genericEventGenerator.h"
#include <string>
#include <curl/curl.h>
#include <exception>
#include <list>
#include <cstdlib>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum class NW_ST{ NW_OK , NW_Fail };

using namespace std;

class networkingEvents :
	public genericEventGenerator
{
public:
	networkingEvents(string account, int NumTweets);
	~networkingEvents();
	bool isStatusOK()
	{
		if (status == NW_ST::NW_OK)
		{
			return true;
		}
		else
			return false;
	}


	virtual eventClass getEvent(void);
	virtual bool hayEvent(void);
	void checkError();
	int stillRunning;
	CURLM *multiHandle;			//Variable donde vamos a atachear los easy handles
private:
	//bool setEvent();
	NW_ST status;
	json j;                    //Variable donde vamos a guardar lo que devuelva Twitter
	CURL *curl;					//Variable donde vamos a guardar las configuraciones de una transferencia
	CURLcode res;
	std::string readString, token;
	std::list<std::string> names;
	static std::size_t myCallback(void *contents, std::size_t size, std::size_t nmemb, void *userp);
	//void printNames(std::list<std::string> names);
	string* fixJson(string* jsonStr);
};

