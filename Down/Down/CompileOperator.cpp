#include "stdafx.h"
#include "CompileOperator.h"


CompileOperator::CompileOperator(Compiler* pNextLevel)
	: pNextLevel(pNextLevel)
{
}

void CompileOperator::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
}

std::map<Token::iToken, string> CompileOperator::getTokenMap()
{
	return tokenMap;
}

CompileOperator::~CompileOperator()
{
	delete pNextLevel;
}
