#include "stdafx.h"


ErrorHandler* ErrorHandler::handler = NULL;
std::list<Error> ErrorHandler::errors = std::list<Error>();


ErrorHandler* ErrorHandler::getInstance()
{
    return handler;
}

void ErrorHandler::addError()
{
	Error::location t = Error::tokenizer;
	std::string s = "Not Defined Error";
	Error erre = Error{s,t};
	errors.push_back(erre);
}

void ErrorHandler::addError(Error::location t, std::string s)
{
    Error err = Error{ s, t };
    errors.push_back(err);
}

void ErrorHandler::addError(Error e)
{
    errors.push_back(e);
}

void ErrorHandler::addThrownError(std::string s)
{

	Error err{ "Thrown Error: " + s ,Error::location::compiler };
	errors.push_back(err);
	
}

void ErrorHandler::addError(Error e, Token::iToken expected, Token::iToken result )
{
	Tokenizer tokert{};
	std::string expt =  tokert.getKeyByValueMappert(expected);
	std::string res = tokert.getKeyByValueMappert(result);
	e.setName("Incorrect token! Expected: '" + expt + "' Result: '" + res + "'");
	errors.push_back(e);
}

void ErrorHandler::addError(std::string s, Token * t)
{
	errors.push_back(Error{ s, ".MD", t->getLevel(), t->getPositie(), Error::error });
}

void ErrorHandler::clearErrors()
{
	errors.clear();
}

std::list<Error> ErrorHandler::getErrors()
{
    return errors;
};

std::string ErrorHandler::asJson()
{
    if (errors.size() == 0)
        return "No errors found";

	

    std::string JSON = "[";
    for (std::list<Error>::iterator it = errors.begin(); it != errors.end(); ++it)
    {
        JSON += (*it).asJsonObject();
        JSON += ",";
    }
    
    JSON = JSON.substr(0, JSON.size()-1);
    
    JSON += "]";
    return JSON;
};

void ErrorHandler::printErrors()
{
    for (std::list<Error>::iterator it = errors.begin(); it != errors.end(); ++it)
    {
        (*it).print();
    }
}

ErrorHandler::~ErrorHandler()
{
}
