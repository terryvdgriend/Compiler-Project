#include "stdafx.h"
#include "CompileEquals.h"
#include "CompileCondition.h"

CompileEquals::CompileEquals() : CompileOperator(make_shared<CompileCondition>())
{
	tokenMap[IToken::EQUALS] = "$=";
}