#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"

class CompileGetArrayItem : public Compiler
{
	public:
		void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);

		void createNewLineToken(shared_ptr<LinkedTokenList>& param, vector<shared_ptr<LinkedTokenList>>& list);

	private:
		string currentArray = "";
			string currentArrayItemTempVar = "";

		bool isMultiDimensional = false;
};