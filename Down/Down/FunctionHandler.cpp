#include "stdafx.h"
#include "FunctionHandler.h"
#include "CommandDictionary.h"

// Singleton prep : required!
shared_ptr<FunctionHandler> FunctionHandler::handler = nullptr;

FunctionHandler::FunctionHandler()
{
	for (auto cf : CommandDictionary::getCustomFunctions())
	{
        auto vecToken = vector<shared_ptr<Token>>();
		addFunction(make_shared<Function>(cf->getName(), cf->getParams(), nullptr, vecToken, nullptr));
		//addFunction(cf);
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