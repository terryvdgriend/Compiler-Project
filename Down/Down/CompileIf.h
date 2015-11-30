#pragma once
#include "Compiler.h"

class CompileIf : public Compiler
{
	public:
		CompileIf();

		void compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
		shared_ptr<Compiler> create();

	private:
		shared_ptr<LinkedActionList> _compiledStatement;
		shared_ptr<LinkedActionList> _condition;
		shared_ptr<LinkedActionList> _body;
		shared_ptr<LinkedActionList> _bodyElse;
		shared_ptr<ActionNode> bodyNode;
		shared_ptr<map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>> _conditionBodyMap;

		void connectLists();
		void connectListsWithElse();
};