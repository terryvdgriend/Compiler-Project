#include "stdafx.h"
#include "CompileUserFunction.h"

#include "CompileCondition.h"

CompileUserFunction::CompileUserFunction() 
{
	/*_compiledStatement = new LinkedActionList();
	_condition = new LinkedActionList();
	_body = new LinkedActionList();
	_compiledStatement->add(new DoNothingNode());*/
}

void CompileUserFunction::Compile(LinkedList & cTokenList, Token & begin, Token & end, LinkedActionList & listActionNodes, ActionNode & actionBefore)
{
	begin = *begin.getPartner();
}

CompileUserFunction::~CompileUserFunction()
{
}
