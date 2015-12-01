#include "stdafx.h"
#include "CompileTimesDivideModulo.h"
#include "CompileSingleStatement.h"

CompileTimesDivideModulo::CompileTimesDivideModulo() : CompileOperator(make_shared<CompileSingleStatement>())
{
	(*tokenMap)[Token::TIMES]	= "$*";
	(*tokenMap)[Token::DIVIDE]	= "$/";
	(*tokenMap)[Token::MODULO]	= "$%";
}

shared_ptr<Compiler> CompileTimesDivideModulo::create()
{
	return make_shared<CompileTimesDivideModulo>();
}