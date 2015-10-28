#pragma once
#include <list>
#include "Error.h"

class ErrorHandler
{

private: 
	ErrorHandler() {};
	static bool instanceFlag;
	static ErrorHandler *handler;
	static std::list<Error> errors;
	~ErrorHandler();

public:
	void ErrorHandler::addError(Error::type t, std::string s);
	void ErrorHandler::addError(Error e);
	static ErrorHandler *getInstance();
	std::list<Error> getErrors();
	
};

