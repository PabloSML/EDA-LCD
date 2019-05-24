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

	void downloadTuits();

	void setEvent(NW_EV_TYPE ev);

	virtual eventClass getEvent(void);
	virtual bool hayEvent(void);
	string getToken(void) { return token; }
	std::list<std::string> getDownloadTuits(void) { return names; }
	std::list<std::string> getDownloadDates(void) { return dates; }

	void checkError();

	//int stillRunning;
	//CURLM *multiHandle;			//Variable donde vamos a atachear los easy handles

private:
	//bool setEvent();
	int stillRunning;
	NW_ST status;
	json j;                    //Variable donde vamos a guardar lo que devuelva Twitter
	CURL *curl;					//Variable donde vamos a guardar las configuraciones de una transferencia
	CURLM *multiHandle;			//Variable donde vamos a atachear los easy handles
	CURLcode res;
	std::string readString, token;
	std::list<std::string> names;
	std::list<std::string> dates;
	std::list<std::string> namesToCopy;
	static std::size_t myCallback(void *contents, std::size_t size, std::size_t nmemb, void *userp);
	//void printNames(std::list<std::string> names);
	string* fixJson(string* jsonStr);
	string account;
	int NumTweets;
};

