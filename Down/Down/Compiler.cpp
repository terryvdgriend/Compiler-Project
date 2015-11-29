#include "stdafx.h"
#include "Compiler.h"

string Compiler::getNextLocalVariableName(string& sBuffer)
{
	static int nValue = 0;
	stringstream sStream;

	sStream << "$" << ++nValue;

	sBuffer = sStream.str();

	return sBuffer;
}

shared_ptr<Token> Compiler::getCurrentToken()
{
	return currentToken;
}

void Compiler::setCurrentToken(Token& nextToken)
{
	currentToken = shared_ptr<Token>(&nextToken);
}