#include "stdafx.h"
#include "FunctionHandler.h"
#include "CommandDictionary.h"

// Singleton prep : required!
shared_ptr<FunctionHandler> FunctionHandler::handler = nullptr;

FunctionHandler::FunctionHandler()
{
	for (pair<string, shared_ptr<BaseCommand>> cf : CommandDictionary::getCustomFunctions())
	{
		addFunction(make_shared<Function>(cf.first, "a", nullptr, vector<shared_ptr<Token>>(), nullptr));
	}
}

shared_ptr<FunctionHandler> FunctionHandler::getInstance()
{
	if (handler == nullptr) 
	{
		handler = shared_ptr<FunctionHandler>(new FunctionHandler());
	}

	return handler;
}

void FunctionHandler::addFunction(shared_ptr<Function> funcion)
{
	functions.push_back(funcion);
}

list<shared_ptr<Function>>& FunctionHandler::getFunctions()
{
	return functions;
}