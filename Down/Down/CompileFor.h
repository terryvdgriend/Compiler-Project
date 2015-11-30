#pragma once
#include "Compiler.h"

class CompileFor : public Compiler
{
private:
	LinkedActionList* _compiledStatement;
	LinkedActionList* _condition;
	LinkedActionList* _body;
	LinkedActionList* _declaration;
	LinkedActionList* _increment;
	ActionNode* bodyNode;
public:
	CompileFor();
	void ConnectLists();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileFor(); };
	~CompileFor();
};
