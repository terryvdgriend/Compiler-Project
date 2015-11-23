#pragma once
#include "LinkedActionList.h"

class Function
{
private:
	std::string _naam;
	std::string _params;
	LinkedActionList* _body;
	bool _userdef = false;
public:
	Function(string naam, std::string params, LinkedActionList* body);
	Function(string naam, std::string params, LinkedActionList* body,bool userdef);
	std::string getName() { return _naam; };
	std::string getParams() { return _params; };
	bool		isUserdef() { return _userdef; };
	LinkedActionList* getBody() { 
		return _body;
	};
	~Function();
};


class FunctionHandler
{
private:
	FunctionHandler() ;
	static bool instanceFlag;
	static FunctionHandler *handler;
	static std::list<Function> functions;
	~FunctionHandler();
public:
		#ifdef _WIN32 //vanwege apple noobs
	void FunctionHandler::addFunction(Function func);
		#else
	void addFunction(Function func);
		#endif

	static FunctionHandler *getInstance();
	std::list<Function> getFunctions();
};


