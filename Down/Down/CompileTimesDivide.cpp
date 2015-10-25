#include "stdafx.h"
#include "CompileTimesDivide.h"
#include "CompileSingleStatement.h"

CompileTimesDivide::CompileTimesDivide() : CompileOperator(new CompileSingleStatement)
{
	map<Token::iToken, string> tokenMap = getTokenMap();
	tokenMap[Token::TIMES] = "$*";
	tokenMap[Token::DIVIDE] = "$/";
}

CompileTimesDivide::~CompileTimesDivide()
{
}