#include "stdafx.h"
#include "CompilePlusMinus.h"
#include "CompileTimesDivideModulo.h"

CompilePlusMinus::CompilePlusMinus() : CompileOperator(make_shared<CompileTimesDivideModulo>())
{
	tokenMap[Token::PLUS]	= "$+";
	tokenMap[Token::MINUS]	= "$-";
}

shared_ptr<Compiler> CompilePlusMinus::create()
{
	return make_shared<CompilePlusMinus>();
}