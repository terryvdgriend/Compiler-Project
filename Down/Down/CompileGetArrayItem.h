#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"

class CompileGetArrayItem : public Compiler
{
	public:
		void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);

	private:
		string currentArray;
		string currentArrayItemTempVar;
};