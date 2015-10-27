#include "stdafx.h"
#include "ErrorHandler.h"

ErrorHandler* ErrorHandler::handler = NULL;

ErrorHandler* ErrorHandler::getInstance()
{
	return handler;
}

void ErrorHandler::addError(Error::type t, std::string s)
{
	//errors.push_back(&Error{ s, t });
}

ErrorHandler::~ErrorHandler()
{
}
