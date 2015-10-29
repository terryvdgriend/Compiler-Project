#pragma once
#include "Compiler.h"

class CompileIf : public Compiler
{
public:
	
	CompileIf();
	~CompileIf();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileIf(); };
private:
	LinkedActionList* _compiledStatement;
	LinkedActionList* _condition;
	LinkedActionList* _body;
	LinkedActionList* _bodyElse;
	ActionNode* bodyNode;
	void ConnectLists();
	void ConnectListsWithElse();
};