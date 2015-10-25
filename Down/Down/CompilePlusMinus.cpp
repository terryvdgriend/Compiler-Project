#include "stdafx.h"
#include "CompilePlusMinus.h"
#include "CompileTimesDivide.h"

CompilePlusMinus::CompilePlusMinus() : CompileOperator(new CompileTimesDivide)
{
	map<Token::iToken, string> tokenMap = getTokenMap();
	tokenMap[Token::PLUS] = "$+";
	tokenMap[Token::MINUS] = "$-";

	// Extended plus and minus operators
	tokenMap[Token::PLUSPLUS] = "$++";
	tokenMap[Token::MINUSMINUS] = "$--";
}

CompilePlusMinus::~CompilePlusMinus()
{
}