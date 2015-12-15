#pragma once
#include "Compiler.h"

class CompileIf : public Compiler
{
	public:
		CompileIf();

		void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);

	private:
		shared_ptr<LinkedActionList> _compiledStatement;
		shared_ptr<LinkedActionList> _condition;
		shared_ptr<LinkedActionList> _body;
		shared_ptr<LinkedActionList> _bodyElse;
		shared_ptr<ActionNode> bodyNode;
		map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>> _conditionBodyMap;

		void connectLists();
		void connectListsWithElse();
};