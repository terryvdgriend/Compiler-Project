#include "stdafx.h"
#include "CompileUnary.h"
#include "CompilePlusMinus.h"

CompileUnary::CompileUnary() : CompileOperator(make_shared<CompilePlusMinus>())
{
	tokenMap[Token::PLUSPLUS]	= "$++";
	tokenMap[Token::MINUSMINUS]	= "$--";
}

shared_ptr<Compiler> CompileUnary::create()
{
	return make_shared<CompileUnary>();
}