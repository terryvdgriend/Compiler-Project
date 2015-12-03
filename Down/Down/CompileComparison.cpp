#include "stdafx.h"
#include "CompileComparison.h"
#include "CompileCondition.h"

CompileComparison::CompileComparison() : CompileOperator(make_shared<CompileCondition>())
{
	// tokenMap[IToken::AND]	= "$&&";
	// tokenMap[IToken::OR]		= "$||";
}

shared_ptr<Compiler> CompileComparison::create()
{ 
	return make_shared<CompileComparison>(); 
};