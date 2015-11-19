#include "stdafx.h"
#include "FunctionHandler.h"

Function::Function(string naam,vector<LinkedActionList> params, LinkedActionList body)
{
	_naam = naam;
	_params = params;
	_body = body;
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
	//gebeurd op veel plekken al, en is lelijk
}

//Dit moet!
FunctionHandler* FunctionHandler::handler = NULL;
std::list<Function> FunctionHandler::functions = std::list<Function>();

FunctionHandler* FunctionHandler::getInstance()
{
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
