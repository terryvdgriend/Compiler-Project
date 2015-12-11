#pragma once
#include "Compiler.h"

class CompileElseIf : public Compiler
{
	public:
		CompileElseIf();

		void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);
		void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore, 
					 map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>& _conditionBodyMap);

	private:
		shared_ptr<LinkedActionList> _compiledStatement;
		shared_ptr<LinkedActionList> _condition;
		shared_ptr<LinkedActionList> _body;
		shared_ptr<ActionNode> bodyNode;

		void connectLists();
};