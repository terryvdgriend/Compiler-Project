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
    #ifdef _WIN32
	void ErrorHandler::addError(Error::location t, std::string s);
	void ErrorHandler::addError();
	void ErrorHandler::addError(Error e);
	void ErrorHandler::addError(std::string s , Token * t);
	void ErrorHandler::addError(Error e, Token::iToken expected, Token::iToken result);
	void ErrorHandler::addThrownError(std::string s);
    void ErrorHandler::printErrors();
	void ErrorHandler::clearErrors();
    #else
    void addError(Error::location t, std::string s);
    void addError();
    void addError(Error e);
    void addError(std::string s , Token * t);
    void addError(Error e, Token::iToken expected, Token::iToken result);
	void addThrownError(std::string s);
    void printErrors();
	void clearErrors();
    #endif
    
	static ErrorHandler *getInstance();
	std::list<Error> getErrors();
	std::string asJson();
};

