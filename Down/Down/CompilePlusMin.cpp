#include "stdafx.h"
#include "CompilePlusMin.h"

#include "CompileMultiply.h"


CompilePlusMin::CompilePlusMin() 
	: CompileOperator(new CompileMultiply)
{
	std::map<Token::iToken, string> tokenMap = getTokenMap();
	tokenMap[Token::PLUS] = "$+";
	tokenMap[Token::MINUS] = "$-";
}


CompilePlusMin::~CompilePlusMin()
{
}
