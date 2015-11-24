#include "stdafx.h"
#include "FunctionHandler.h"

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
	//Toevoegen van standaard functies, hier????????
	//gebeurd op veel plekken al, en is lelijk //TODO: code cleanup op andere plekken
	//this->addFunction(Function{"printdown","s",nullptr});//s=string
	this->addFunction(Function{ "printdown","a",nullptr,{},nullptr }); //a = all / any
	this->addFunction(Function{ "printup","s",nullptr,{},nullptr });
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
