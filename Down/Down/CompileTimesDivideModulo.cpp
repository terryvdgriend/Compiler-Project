#include "stdafx.h"
#include "CompileTimesDivideModulo.h"
#include "CompileSingleStatement.h"

CompileTimesDivideModulo::CompileTimesDivideModulo() : CompileOperator(new CompileSingleStatement)
{
	TokenMap &tokenMap = getTokenMap();
	tokenMap[Token::TIMES] = "$*";
	tokenMap[Token::DIVIDE] = "$/";
	tokenMap[Token::MODULO] = "$%";
}

CompileTimesDivideModulo::~CompileTimesDivideModulo()
{
	//delete pNextLevel;
}
