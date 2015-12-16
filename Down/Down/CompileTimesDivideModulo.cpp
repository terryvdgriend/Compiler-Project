#include "stdafx.h"
#include "CompileTimesDivideModulo.h"
#include "CompileSingleStatement.h"

CompileTimesDivideModulo::CompileTimesDivideModulo() : CompileOperator(make_shared<CompileSingleStatement>())
{
	tokenMap[IToken::TIMES]		= "$*";
	tokenMap[IToken::DIVIDE]	= "$/";
	tokenMap[IToken::MODULO]	= "$%";
}