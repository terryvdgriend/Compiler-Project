#include "stdafx.h"
#include "CompileMultiply.h"


CompileMultiply::CompileMultiply()
{
	std::map<Token::iToken, string> tokenMap = getTokenMap();
	tokenMap[Token::TIMES] = "$*";
	tokenMap[Token::DIVIDE] = "$/";
}


CompileMultiply::~CompileMultiply()
{
}
