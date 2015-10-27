#include "stdafx.h"
#include "CompileMultiply.h"

#include "CompileSingleStatement.h"


CompileMultiply::CompileMultiply()
	: CompileOperator(new CompileSingleStatement)
{
	TokenMap &tokenMap = getTokenMap();
	tokenMap[Token::TIMES] = "$*";
	tokenMap[Token::DIVIDE] = "$/";
}


CompileMultiply::~CompileMultiply()
{
}
