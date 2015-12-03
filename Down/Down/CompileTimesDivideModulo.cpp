#include "stdafx.h"
#include "CompileTimesDivideModulo.h"
#include "CompileSingleStatement.h"

CompileTimesDivideModulo::CompileTimesDivideModulo() : CompileOperator(make_shared<CompileSingleStatement>())
{
	tokenMap[IToken::TIMES]		= "$*";
	tokenMap[IToken::DIVIDE]	= "$/";
	tokenMap[IToken::MODULO]	= "$%";
}

shared_ptr<Compiler> CompileTimesDivideModulo::create()
{
	return make_shared<CompileTimesDivideModulo>();
}