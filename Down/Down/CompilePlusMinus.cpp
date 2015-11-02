#include "stdafx.h"
#include "CompilePlusMinus.h"
#include "CompileTimesDivideModulo.h"

CompilePlusMinus::CompilePlusMinus() : CompileOperator(new CompileTimesDivideModulo)
{
	TokenMap &tokenMap = getTokenMap();
	tokenMap[Token::PLUS] = "$+";
	tokenMap[Token::MINUS] = "$-";

	// Extended plus and minus operators
	tokenMap[Token::PLUSPLUS] = "$++";
	tokenMap[Token::MINUSMINUS] = "$--";
}

CompilePlusMinus::~CompilePlusMinus()
{
}