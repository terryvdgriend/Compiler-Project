#include "stdafx.h"
#include "CompilePlusMin.h"

#include "CompileMultiply.h"


CompilePlusMin::CompilePlusMin() 
	: CompileOperator(new CompileMultiply)
{
	TokenMap &tokenMap = getTokenMap();
	tokenMap[Token::PLUS] = "$+";
	tokenMap[Token::MINUS] = "$-";
}


CompilePlusMin::~CompilePlusMin()
{
}
