#pragma once
#include <list>
#include "Error.h"

class ErrorHandler
{
private: 
	static bool instanceFlag;
	static ErrorHandler *handler;
	ErrorHandler() {};
	static std::list<Error*> errors;
	
public:
	static ErrorHandler *getInstance();
	void ErrorHandler::addError(Error::type t, std::string s);
	~ErrorHandler();
};

