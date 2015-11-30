#include "stdafx.h"
#include "CompileUnary.h"
#include "CompilePlusMinus.h"

CompileUnary::CompileUnary() : CompileOperator(new CompilePlusMinus)
{
	TokenMap &tokenMap = getTokenMap();
	tokenMap[Token::PLUSPLUS] = "$++";
	tokenMap[Token::MINUSMINUS] = "$--";
}

CompileUnary::~CompileUnary()
{
}