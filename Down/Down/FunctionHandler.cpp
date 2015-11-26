#include "stdafx.h"
#include "FunctionHandler.h"
#include "CommandDictionary.h"

Function::Function(string naam, std::string params, LinkedList* body, std::vector<Token*> paramTokens, Token* returnToken)
{
	_naam = naam;
	_params = params;
	_paramTokens = paramTokens;
	_returnToken = returnToken;
	_body = body;
}
Function::Function(string naam, std::string params, LinkedList * body, std::vector<Token*> paramTokes, Token* returnToken, bool userdef)
{
	_naam = naam;
	_params = params;
	_paramTokens = paramTokes;
	_body = body;
	_returnToken = returnToken;
	_userdef = userdef;
}
Function::~Function()
{
}

//////////////////////////
////////// Handler ///////
//////////////////////////

FunctionHandler::FunctionHandler()
{
	for (std::pair<string, shared_ptr<BaseCommand>> cf : CommandDictionary::CustFunc())
	{
		this->addFunction(Function{ cf.first,"a",nullptr,{},nullptr });
		//this->addFunction(Function{ cf.first,"aa",nullptr,{},nullptr });
		//this->addFunction(Function{ cf.first,"aaa",nullptr,{},nullptr });
	}
}

//Dit moet!
FunctionHandler* FunctionHandler::handler = nullptr;
std::list<Function> FunctionHandler::functions = std::list<Function>();

FunctionHandler* FunctionHandler::getInstance()
{
	if (handler == nullptr) {
		handler = new FunctionHandler();
	}
	return handler;
}

void FunctionHandler::addFunction(Function func)
{
	functions.push_back(func);
}

std::list<Function> FunctionHandler::getFunctions()
{
	return functions;
}

FunctionHandler::~FunctionHandler()
{
}
