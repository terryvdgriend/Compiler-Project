#include "stdafx.h"
#include "CompileFunction.h"


CompileFunction::CompileFunction()
{
	std::map<Token::iToken, string> tokenMap = getTokenMap();
	//tokenMap[Token::PrintDingen:)] = "$IETSMETPRINTENOFANDEREFUNCTIESHIERO";
}


CompileFunction::~CompileFunction()
{
}
