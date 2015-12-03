#include "stdafx.h"
#include "CompileFunction.h"
#include "CompileCondition.h"

CompileFunction::CompileFunction() : CompileOperator(make_shared<CompileCondition>())
{
	tokenMap[IToken::PRINT]		= "$PRINTDOWN";
	tokenMap[IToken::PRINTUP]	= "$PRINTUP";
}

shared_ptr<Compiler> CompileFunction::create()
{
	return make_shared<CompileFunction>();
}