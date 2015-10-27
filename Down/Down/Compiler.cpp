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

std::string Compiler::getNextLocalVariableName(std::string& sBuffer)
{
	static  int         nValue = 0;
	std::stringstream   sStream;

	sStream << " " << ++nValue;

	sBuffer = sStream.str();

	return sBuffer;
}
