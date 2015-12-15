#include "stdafx.h"
#include "Compiler.h"

#include <sstream>

/*
Compiler::Compiler()
{
}


Compiler::~Compiler()
{
}*/

string Compiler::getNextLocalVariableName(string& sBuffer)
{
	static int nValue = 0;
	stringstream   sStream;

	sStream << "$" << ++nValue;

	nValueCount = nValue;

	sBuffer = sStream.str();

	return sBuffer;
}

string Compiler::getPreviousLocalVariableName(string& sBuffer)
{
	stringstream   sStream;

	sStream << "$" << --nValueCount;

	sBuffer = sStream.str();

	return sBuffer;
}

string Compiler::getCurrentLocalVariableName()
{
	stringstream   sStream;

	sStream << "$" << nValueCount;

	return sStream.str();
}