#include "stdafx.h"
#include "CompileOperator.h"


CompileOperator::CompileOperator()
{
}

void CompileOperator::Compile(LinkedList& cTokenList, LinkedList& begin, LinkedList& end, LinkedActionList listActionNodes, ActionNode actionBefore)
{
}

std::map<Token::iToken, string> CompileOperator::getTokenMap()
{
	return tokenMap;
}

CompileOperator::~CompileOperator()
{
}
