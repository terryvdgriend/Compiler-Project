#include "stdafx.h"
#include "CompileEquals.h"
#include "CompileCondition.h"

CompileEquals::CompileEquals()
	: CompileOperator(new CompileCondition)
{
	TokenMap &tokenMap = getTokenMap();
	tokenMap[Token::EQUALS] = "$=";
}


CompileEquals::~CompileEquals()
{
}
