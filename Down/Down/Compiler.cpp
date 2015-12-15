#include "stdafx.h"
#include "Compiler.h"

Compiler::Compiler()
{
	currentToken = nullptr;
}

string Compiler::getNextLocalVariableName(string& sBuffer)
{
	static int nValue = 0;
	stringstream sStream;

	sStream << "$" << ++nValue;

	nValueCount = nValue;

	sBuffer = sStream.str();

	return sBuffer;
}

string Compiler::getCurrentLocalVariableName()
{
	stringstream sStream;

	sStream << "$" << nValueCount;

	return sStream.str();
}

string Compiler::getPreviousLocalVariableName(string& sBuffer)
{
	stringstream sStream;

	sStream << "$" << --nValueCount;

	sBuffer = sStream.str();

	return sBuffer;
}

shared_ptr<Token> Compiler::getCurrentToken()
{
	return currentToken;
}

void Compiler::setCurrentToken(shared_ptr<Token>& nextToken)
{
	currentToken = nextToken;
}