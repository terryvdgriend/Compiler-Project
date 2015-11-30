#pragma once
#include "Compiler.h"

class CompileFor : public Compiler
{
	public:
		CompileFor();

		void compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
		shared_ptr<Compiler> create();

	private:
		shared_ptr<LinkedActionList> _compiledStatement;
		shared_ptr<LinkedActionList> _condition;
		shared_ptr<LinkedActionList> _body;
		shared_ptr<LinkedActionList> _declaration;
		shared_ptr<LinkedActionList> _increment;
		shared_ptr<ActionNode> bodyNode;

		void connectLists();
};