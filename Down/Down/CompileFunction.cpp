#include "stdafx.h"
#include "CompileFunction.h"


#include "CompileCondition.h"

CompileFunction::CompileFunction()
	: CompileOperator(new CompileCondition)
{
	std::map<Token::iToken, string> tokenMap = getTokenMap();
	//tokenMap[Token::PrintDingen:)] = "$IETSMETPRINTENOFANDEREFUNCTIESHIERO";
}


CompileFunction::~CompileFunction()
{
}
