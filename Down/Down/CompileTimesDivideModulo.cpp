#include "stdafx.h"
#include "CompileTimesDivideModulo.h"
#include "CompileSingleStatement.h"

CompileTimesDivideModulo::CompileTimesDivideModulo() : CompileOperator(new CompileSingleStatement)
{
	map<Token::iToken, string> tokenMap = getTokenMap();
	tokenMap[Token::TIMES] = "$*";
	tokenMap[Token::DIVIDE] = "$/";
	tokenMap[Token::MODULO] = "$%";
}

CompileTimesDivideModulo::~CompileTimesDivideModulo()
{
}