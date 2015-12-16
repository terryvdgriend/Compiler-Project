#include "stdafx.h"
#include "CompilePlusMinus.h"
#include "CompileTimesDivideModulo.h"

CompilePlusMinus::CompilePlusMinus() : CompileOperator(make_shared<CompileTimesDivideModulo>())
{
	tokenMap[IToken::PLUS]	= "$+";
	tokenMap[IToken::MINUS]	= "$-";
}