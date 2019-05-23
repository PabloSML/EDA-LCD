#include "networkingEvents.h"



networkingEvents::networkingEvents(string account, int NumTweets)
{
	status = NW_ST::NW_OK;

	// Query es la dirección de Twitter que vamos a consultar. vamos a bajar los &count twits de screen_name en formato JSON.
	std::string query = "https://api.twitter.com/1.1/statuses/user_timeline.json?screen_name=";
	query += account + "&count=" + std::to_string(NumTweets);

	// Las dos constantes de abajo son el API_Key y API_SecretKey que necesita Twitter para realizar la autenticación de nuestra App
	// y por lo tanto permitirnos el acceso a sus servidores. Son parte de la estrategia de autenticación Oauth2.
	//Ambas se obtienen de la app que creen en la pagina de Twitter
	std::string API_key = "HCB39Q15wIoH61KIkY5faRDf6";
	std::string API_SecretKey = "7s8uvgQnJqjJDqA6JsLIFp90FcOaoR5Ic41LWyHOic0Ht3SRJ6";


	

	/************************************************************************************
	*                      Get Bearer Token from the Twitter API						*
	************************************************************************************/

	// Primero realizamos la inicialización de curl para obtener el token de Twitter el cual vamos
	// a utilizar luego para realizar la autenticación por Oauth2.
	curl = curl_easy_init();
	if (curl)
	{
		//Seteamos primero la pagina donde nos vamos a conectar. Para buscar el token es siempre la misma
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.twitter.com/oauth2/token");

		// Si la página nos redirije a algún lado, le decimos a curl que siga dicha redirección.
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		// Le decimos a CURL que trabaje tanto con HTTP como HTTPS, Autenticación por HTTP en modo básico.
		curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
		curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);

		//Preparamos el password para la autenticación
		string userPwd = API_key + ":" + API_SecretKey;

		//Se lo seteamos a CURL.
		curl_easy_setopt(curl, CURLOPT_USERPWD, userPwd.c_str());

		struct curl_slist *list = NULL;
		//Pueden setear el Header con la linea de abajo, pero necesitan codificar las claves en Base64
		//list = curl_slist_append(list, "Authorization: Basic YlB5alk1bWRMR2V4TlhPTHhSUjd3MUVjUzpkR2liU3FIcURrektQMUtPbzFJTjRBd21tZGI1Tnl5ZjBFQTZkTDBLWlpmZDE0ZnhQQw==");

		//Le decimos a CURL que vamos a mandar URLs codificadas y además en formato UTF8.
		list = curl_slist_append(list, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

		//Le decimos a CURL que trabaje con credentials.
		std::string data = "grant_type=client_credentials";
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

		//Le decimos a curl que cuando haya que escribir llame a myCallback
		//y que use al string readString como user data.
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, myCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readString);

		// Perform the request, res will get the return code
		// Con lo de abajo le decimos a curl que intente conectarse a la página (recordemos que la idea es
		// obtener la autenticación así luego Twitter nos deja conectarnos a cualquier usuario público)
		//Recordar que easy_perform es bloqueante, en este caso es correcto asi al ser inicializacion y no tardar mucho tiempo.
		res = curl_easy_perform(curl);

		// Nos fijamos si hubo algún error
		if (res != CURLE_OK)
		{
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
			//Hacemos un clean up de curl antes de salir.
			curl_easy_cleanup(curl);
			status = NW_ST::NW_Fail;
			return;
		}

		// Si no hubo errores hago un clean up antes de realizar un nuevo query.
		curl_easy_cleanup(curl);

		//Si el request de CURL fue exitoso entonces twitter devuelve un JSON
		//Abajo busco el token en el JSON para luego acceder a los twits.
		j = json::parse(readString);

		//Se encierra el parseo en un bloque try-catch porque la libreria maneja errores por excepciones.
		//Pueden tambien parsear usando iteradores o la forma que quieras, buscar en la documentacion las diferentes formas.
		try
		{
			//Tratamos de acceder al campo acces_token del JSON
			std::string aux = j["access_token"];
			token = aux;
			std::cout << "Bearer Token get from Twitter API: \n" << token << std::endl;
		}
		catch (std::exception& e)
		{
			//Si hubo algun error, se muestra el error que devuelve la libreria
			std::cerr << e.what() << std::endl;
			status = NW_ST::NW_Fail;
			return;
		}
	}
	else
	{
		std::cout << "Cannot download tweets. Unable to start cURL" << std::endl;
		status = NW_ST::NW_Fail;
		return;
	}

	//Una vez obtenido el Token ahora voy a buscar los Twits

/************************************************************************************
*                        Get Tweets from the Twitter API							*
************************************************************************************/

// Nuevamente reinicializo todo curl.
	curl = curl_easy_init();
	multiHandle = curl_multi_init();
	readString = "";
	stillRunning = 0;
	if ((curl != NULL) & (multiHandle != NULL))
	{
		//Attacheo el easy handle para manejar una coneccion no bloqueante.
		curl_multi_add_handle(multiHandle, curl);

		//Seteamos URL FOLLOWLOCATION y los protocolos a utilizar igual que antes.
		curl_easy_setopt(curl, CURLOPT_URL, query.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);

		//Construimos el Header de autenticacion como lo especifica la API
		//usando el token que obtuvimos antes
		struct curl_slist *list = NULL;
		std::string aux = "Authorization: Bearer ";
		aux = aux + token;
		list = curl_slist_append(list, aux.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

		//Seteamos los callback igual que antes
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, myCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readString);

		//Realizamos ahora un perform no bloqueante
		curl_multi_perform(multiHandle, &stillRunning);
	}
	else
	{
		status = NW_ST::NW_Fail;
	}
}


networkingEvents::~networkingEvents()
{
}

eventClass
networkingEvents::getEvent(void)
{
	return myEvent;
}

bool
networkingEvents::hayEvent(void)
{
	return false;	
}

bool
setEvent(void)
{
	return false; 
}


//Concatena lo recibido en content a s
std::size_t networkingEvents::myCallback(void *contents, std::size_t size, std::size_t nmemb, void *userp)
{
	std::size_t realsize = size * nmemb;
	char* data = (char *)contents;
	std::string* s = (std::string*)userp;
	s->append(data, realsize);
	return realsize;			//recordar siempre devolver realsize
}


void networkingEvents::checkError(void)	//luego de llamar a esta funcion hay  que comprobar el status
{
	//Checkeamos errores
	if (res != CURLE_OK)
	{
		std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		status = NW_ST::NW_Fail;
	}

	//Siempre realizamos el cleanup al final
	curl_easy_cleanup(curl);

	// Se verifica el estado del json al terminar la conexion
	
	try
	{
		j = json::parse(readString);
	}
	catch (exception& e)
	{
		j = json::parse(*fixJson(&readString));
	}
}

string* 
networkingEvents::fixJson(string* jsonStr)
{
	int beg, end, lastValid = jsonStr->find_first_of('[');
	int count = 0;
	bool done = false;
	beg = jsonStr->find_first_of('{');	// se asume que hay por lo menos una llave abierta
	count++;

	do {
		beg = jsonStr->find_first_of("{}");
		if (beg != string::npos)
		{
			if ((*jsonStr)[beg] == '{')
				count++;
			else
				count--;
			if (!count)
				lastValid = beg;
			beg++;
		}
		else
			done = true;
	} while (!done);

	if (!count)
	{
		beg = 0;
		end = lastValid + 1;
		string temp = jsonStr->substr(beg, end - beg) + "]";
		*jsonStr = temp;
	}

	return jsonStr;
}