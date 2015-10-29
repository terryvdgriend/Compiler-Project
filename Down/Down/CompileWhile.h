#pragma once
#include "Compiler.h"

class CompileWhile : public Compiler
{
private:
	LinkedActionList* _compiledStatement;
	LinkedActionList* _condition;
	LinkedActionList* _body;
	ActionNode* bodyNode;
public:
	CompileWhile();
	void ConnectLists();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileWhile(); };
	~CompileWhile();
};
