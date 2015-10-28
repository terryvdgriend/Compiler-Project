#include "stdafx.h"

ErrorHandler* ErrorHandler::handler = NULL;
std::list<Error> ErrorHandler::errors = std::list<Error>();


ErrorHandler* ErrorHandler::getInstance()
{
	return handler;
}

void ErrorHandler::addError(Error::type t, std::string s)
{
	Error err = Error{ s, t };
	errors.push_back(err);
}

void ErrorHandler::addError(Error e)
{
	errors.push_back(e);
}

std::list<Error> ErrorHandler::getErrors()
{ 
	return errors;
};

ErrorHandler::~ErrorHandler()
{
}
