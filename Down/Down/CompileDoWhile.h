#pragma once
#include "Compiler.h"

class CompileDoWhile : public Compiler
{
	public:
		CompileDoWhile();

		void compile(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end, 
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);
		shared_ptr<Compiler> create();

	private:
		shared_ptr<LinkedActionList> _compiledStatement;
		shared_ptr<LinkedActionList> _condition;
		shared_ptr<LinkedActionList> _body;
		shared_ptr<ActionNode> bodyNode;

		void connectLists();
};