#include "stdafx.h"
#include "CompileEquals.h"
#include "CompileComparison.h"

CompileEquals::CompileEquals() : CompileOperator(make_shared<CompileComparison>())
{
	tokenMap[IToken::EQUALS] = "$=";
}