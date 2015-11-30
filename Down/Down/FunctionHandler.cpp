#include "stdafx.h"
#include "FunctionHandler.h"
#include "CommandDictionary.h"

// Singleton prep : required!
shared_ptr<FunctionHandler> FunctionHandler::handler = nullptr;

FunctionHandler::FunctionHandler()
{
	for (pair<string, shared_ptr<BaseCommand>> cf : CommandDictionary::CustFunc())
	{
		addFunction(make_shared<Function>(cf.first, "a", nullptr, nullptr, nullptr));
	}
	functions = shared_ptr<list<shared_ptr<Function>>>();
}

shared_ptr<FunctionHandler> FunctionHandler::getInstance()
{
	if (handler == nullptr) 
	{
		handler = make_shared<FunctionHandler>();
	}

	return handler;
}

void FunctionHandler::addFunction(shared_ptr<Function>& funcion)
{
	functions->push_back(funcion);
}

shared_ptr<list<shared_ptr<Function>>> FunctionHandler::getFunctions()
{
	return functions;
}