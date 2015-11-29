#pragma once
#include "Compiler.h"

class CompileIf : public Compiler
{
	public:
		CompileIf();
		~CompileIf();
		void compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
		Compiler * create() { return new CompileIf(); };
	private:
		LinkedActionList* _compiledStatement;
		LinkedActionList* _condition;
		LinkedActionList* _body;
		LinkedActionList* _bodyElse;
		ActionNode* bodyNode;
		void ConnectLists();
		void ConnectListsWithElse();
		std::map<LinkedActionList*, LinkedActionList*> _conditionBodyMap;
};