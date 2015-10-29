#pragma once
#include <list>
#include "Error.h"
#include "Text.h"
#include "Tokenizer.h"

class ErrorHandler
{

private: 
	ErrorHandler() {};
	static bool instanceFlag;
	static ErrorHandler *handler;
	static std::list<Error> errors;
	~ErrorHandler();

public:
	void ErrorHandler::addError(Error::location t, std::string s);
	void ErrorHandler::addError(Error e);
	void ErrorHandler::addError(Error e, Token::iToken expected, Token::iToken result);
	static ErrorHandler *getInstance();
	std::list<Error> getErrors();
	std::string asJson();
	void ErrorHandler::printErrors();
};

