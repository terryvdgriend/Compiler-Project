#include "stdafx.h"
#include "CompileComparison.h"
#include "CompileCondition.h"

CompileComparison::CompileComparison() : CompileOperator(new CompileCondition)
{
	//TokenMap &tokenMap = getTokenMap();
	//tokenMap[Token::AND] = "$&&"; //TODO deze 2 
	//tokenMap[Token::OR] = "$||";
}

shared_ptr<Compiler> CompileComparison::create()
{ 
	return make_shared<CompileComparison>(); 
};