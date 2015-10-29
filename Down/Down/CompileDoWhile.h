#pragma once
#include "Compiler.h"
class CompileDoWhile :
	public Compiler
{
private:
	LinkedActionList* _compiledStatement;
	LinkedActionList* _condition;
	LinkedActionList* _body;
	ActionNode* bodyNode;
public:
	CompileDoWhile();
	void ConnectLists();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileDoWhile(); };
	~CompileDoWhile();
};