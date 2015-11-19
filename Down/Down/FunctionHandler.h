#pragma once
#include "LinkedActionList.h"

class Function
{
private:
	std::string _naam;
	vector<LinkedActionList*> _params;
	LinkedActionList* _body;
public:
	Function(string naam, vector<LinkedActionList*> params, LinkedActionList* body);
	std::string getName() { return _naam; };
	vector<LinkedActionList*> getParams() { return _params; };
	LinkedActionList* getBody() { 
		return new LinkedActionList(*_body);
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


