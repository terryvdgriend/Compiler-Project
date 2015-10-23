#include "stdafx.h"
#include "CompileEquals.h"


CompileEquals::CompileEquals()
{
	std::map<Token::iToken, string> tokenMap = getTokenMap();
	tokenMap[Token::EQUALS] = "$=";
}


CompileEquals::~CompileEquals()
{
}
