#include "stdafx.h"
#include "CompileUnary.h"
#include "CompilePlusMinus.h"

CompileUnary::CompileUnary() : CompileOperator(make_shared<CompilePlusMinus>())
{
	tokenMap[IToken::PLUSPLUS]		= "$++";
	tokenMap[IToken::MINUSMINUS]	= "$--";
}