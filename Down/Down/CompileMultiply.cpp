#include "stdafx.h"
#include "CompileMultiply.h"

#include "CompileSingleStatement.h"


CompileMultiply::CompileMultiply()
	: CompileOperator(new CompileSingleStatement)
{
	std::map<Token::iToken, string> tokenMap = getTokenMap();
	tokenMap[Token::TIMES] = "$*";
	tokenMap[Token::DIVIDE] = "$/";
}


CompileMultiply::~CompileMultiply()
{
}
