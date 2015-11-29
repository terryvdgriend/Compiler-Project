#include "stdafx.h"
#include "CompilePlusMinus.h"
#include "CompileTimesDivideModulo.h"

CompilePlusMinus::CompilePlusMinus() : CompileOperator(new CompileTimesDivideModulo)
{
	TokenMap &tokenMap = getTokenMap();
	tokenMap[Token::PLUS] = "$+";
	tokenMap[Token::MINUS] = "$-";
}

CompilePlusMinus::~CompilePlusMinus()
{
}