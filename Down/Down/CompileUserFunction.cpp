#include "stdafx.h"
#include "CompileUserFunction.h"

#include "CompileCondition.h"

CompileUserFunction::CompileUserFunction() 
	: CompileOperator(new CompileCondition)
{
	TokenMap &tokenMap = getTokenMap();
	tokenMap[Token::FUNCTION] = "$UFUNC";
}


CompileUserFunction::~CompileUserFunction()
{
}
