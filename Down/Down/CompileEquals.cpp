#include "stdafx.h"
#include "CompileEquals.h"
#include "CompileCondition.h"

CompileEquals::CompileEquals()
	: CompileOperator(new CompileCondition)
{
	std::map<Token::iToken, string> tokenMap = getTokenMap();
	tokenMap[Token::EQUALS] = "$=";
}


CompileEquals::~CompileEquals()
{
}
