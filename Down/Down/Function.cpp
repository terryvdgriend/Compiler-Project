#include "stdafx.h"
#include "Function.h"

Function::Function(string name, string params, shared_ptr<LinkedList> body, vector<shared_ptr<Token>>& paramTokens, shared_ptr<Token> returnToken)
{																									 
	_name			= name;																			 
	_params			= params;																		 
	_paramTokens	= paramTokens;																	 
	_returnToken	= returnToken;																	 
	_body			= body;																			 
	_userDefined	= false;																		 
}																									 
																									 
Function::Function(string name, string params, shared_ptr<LinkedList> body, vector<shared_ptr<Token>>& paramTokens, shared_ptr<Token> returnToken, bool userDefined)
{
	_name			= name;
	_params			= params;
	_paramTokens	= paramTokens;
	_body			= body;
	_returnToken	= returnToken;
	_userDefined	= userDefined;
}

string Function::getName()
{
	return _name;
}

string Function::getParams()
{
	return _params;
}

vector<shared_ptr<Token>>& Function::getParamTokens()
{
	return _paramTokens;
}

shared_ptr<Token> Function::getReturn()
{
	return _returnToken;
}

shared_ptr<LinkedList> Function::getBody()
{
	return _body;
}

bool Function::isUserDefined()
{
	return _userDefined;
}