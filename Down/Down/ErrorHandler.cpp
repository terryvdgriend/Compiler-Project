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
	ErrorLocation errorLocation = ErrorLocation::tokenizer;
	string errorMessage = "Not Defined Error";
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

void ErrorHandler::addError(shared_ptr<Error>& error, Token::iToken expected, Token::iToken result)
{
	unique_ptr<Tokenizer> tokenizer = make_unique<Tokenizer>();
	string exptation = tokenizer->getKeyByValueMappert(expected);
	string actualResult = tokenizer->getKeyByValueMappert(result);
	error->setName("Incorrect token! Expected: '" + exptation + "' Result: '" + actualResult + "'");

	errors.push_back(error);
}

void ErrorHandler::addError(string errorName, shared_ptr<Token>& token)
{
	shared_ptr<Error> error = make_shared<Error>(errorName, ".MD", token->getLevel(), token->getPositie(), ErrorType::error);

	errors.push_back(error);
}