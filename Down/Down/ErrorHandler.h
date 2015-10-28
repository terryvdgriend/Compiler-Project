#pragma once
#include <list>
#include "Error.h"
#include "Text.h"

class ErrorHandler
{

private: 
	ErrorHandler() {};
	static bool instanceFlag;
	static ErrorHandler *handler;
	static std::list<Error> errors;
	~ErrorHandler();

public:
	static ErrorHandler *getInstance();
	void ErrorHandler::addError(Error::type t, std::string s);
	void ErrorHandler::addError(Error e);
	std::list<Error> getErrors();
	std::string asJson();
	void ErrorHandler::printErrors();
};

