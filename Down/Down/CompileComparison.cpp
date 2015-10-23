#include "stdafx.h"
#include "CompileComparison.h"
#include "CompileCondition.h"


CompileComparison::CompileComparison()
	: CompileOperator(new CompileCondition)
{
	std::map<Token::iToken, string> tokenMap = getTokenMap();
	//tokenMap[Token::AND] = "$&&"; //TODO deze 2 
	//tokenMap[Token::OR] = "$||";
}


CompileComparison::~CompileComparison()
{
}
