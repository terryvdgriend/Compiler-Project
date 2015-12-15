#include "stdafx.h"
#include "Tokenizer.h"

// Singleton prep : required!
shared_ptr<ErrorHandler> ErrorHandler::handler = nullptr;

ErrorHandler::ErrorHandler()
{
	//
}

shared_ptr<ErrorHandler> ErrorHandler::getInstance()
{
	if (handler == nullptr)
	{
		handler = shared_ptr<ErrorHandler>(new ErrorHandler());
	}

	return handler;
}

list<shared_ptr<Error>>& ErrorHandler::getErrors()
{
	return errors;
}

void ErrorHandler::printErrors()
{
	for (list<shared_ptr<Error>>::iterator it = errors.begin(); it != errors.end(); ++it)
	{
		(*it)->print();
	}
}

void ErrorHandler::clearErrors()
{
	errors.clear();
}

string ErrorHandler::asJson()
{
	if (errors.size() == 0)
	{
		return "No errors found";
	}
	string JSON = "[";

	for (list<shared_ptr<Error>>::iterator it = errors.begin(); it != errors.end(); ++it)
	{
		JSON += (*it)->asJsonObject();
		JSON += ",";
	}
	JSON = JSON.substr(0, JSON.size() - 1);
	JSON += "]";

	return JSON;
}

void ErrorHandler::addError()
{
	ErrorLocation errorLocation = ErrorLocation::TOKENIZER;
	string errorMessage = "Undefined Error";
	shared_ptr<Error> error = make_shared<Error>(errorMessage, errorLocation);
	errors.push_back(error);
}

void ErrorHandler::addError(string errorName, ErrorLocation errorLocation)
{
	shared_ptr<Error> error = make_shared<Error>(errorName, errorLocation);
    errors.push_back(error);
}

void ErrorHandler::addError(shared_ptr<Error>& error)
{
    errors.push_back(error);
}

void ErrorHandler::addError(string errorName, shared_ptr<Token>& token)
{
	shared_ptr<Error> error = make_shared<Error>(errorName, ".MD", token->getLineNumber(), token->getPosition(), ErrorType::ERROR);
	errors.push_back(error);
}

void ErrorHandler::addError(shared_ptr<Error>& error, IToken expected, IToken result)
{
	Tokenizer tokenizer;
	string exptation = tokenizer.getKeyByValueTokenMap(expected);
	string actualResult = tokenizer.getKeyByValueTokenMap(result);
	error->setName("Incorrect token! Expected: '" + exptation + "' Result: '" + actualResult + "'");
	errors.push_back(error);
}

void ErrorHandler::addThrownError(string errorName)
{
	shared_ptr<Error> error = make_shared<Error>("Thrown Error: " + errorName, ErrorLocation::COMPILER);
	errors.push_back(error);
}