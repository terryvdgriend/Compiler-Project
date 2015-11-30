#pragma once
#include "Compiler.h"

class CompileDoWhile : public Compiler
{
	public:
		CompileDoWhile();

		void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
		shared_ptr<Compiler> create();

	private:
		shared_ptr<LinkedActionList> _compiledStatement;
		shared_ptr<LinkedActionList> _condition;
		shared_ptr<LinkedActionList> _body;
		shared_ptr<ActionNode> bodyNode;

		void connectLists();
};