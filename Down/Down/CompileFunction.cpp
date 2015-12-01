#include "stdafx.h"
#include "CompileFunction.h"
#include "CompileCondition.h"

CompileFunction::CompileFunction() : CompileOperator(make_shared<CompileCondition>())
{
	(*tokenMap)[Token::PRINT]	= "$PRINTDOWN";
	(*tokenMap)[Token::PRINTUP] = "$PRINTUP";
}

shared_ptr<Compiler> CompileFunction::create()
{
	return make_shared<CompileFunction>();
}