#pragma once
#include "Compiler.h"

class CompileElseIf : public Compiler
{
public:

	CompileElseIf();
	~CompileElseIf();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileElseIf(); };
private:
	LinkedActionList* _compiledStatement;
	LinkedActionList* _condition;
	LinkedActionList* _body;
	ActionNode* bodyNode;
	void ConnectLists();
};