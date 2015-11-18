#include "stdafx.h"
#include "CompileFunction.h"


#include "CompileCondition.h"

CompileFunction::CompileFunction()
	: CompileOperator(new CompileCondition)
{
	TokenMap &tokenMap = getTokenMap();
	tokenMap[Token::PRINT] = "$PRINTDOWN";
	tokenMap[Token::PRINTUP] = "$PRINTUP";
}


CompileFunction::~CompileFunction()
{
}
