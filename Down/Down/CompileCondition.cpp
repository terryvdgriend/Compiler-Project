#include "stdafx.h"
#include "CompileCondition.h"
#include "CompileUnary.h"

CompileCondition::CompileCondition() : CompileOperator(make_shared<CompileUnary>())
{
	(*tokenMap)[Token::LARGER_THAN]	= "$>";
	(*tokenMap)[Token::LESS_THAN]	= "$<";
	(*tokenMap)[Token::EQUALS_TO]	= "$==";
}

shared_ptr<Compiler> CompileCondition::create()
{
	return make_shared<CompileCondition>();
}