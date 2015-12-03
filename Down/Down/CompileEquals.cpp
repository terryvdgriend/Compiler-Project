#include "stdafx.h"
#include "CompileEquals.h"
#include "CompileCondition.h"

CompileEquals::CompileEquals() : CompileOperator(make_shared<CompileCondition>())
{
	tokenMap[Token::EQUALS] = "$=";
}

shared_ptr<Compiler> CompileEquals::create()
{
	return make_shared<CompileEquals>();
}