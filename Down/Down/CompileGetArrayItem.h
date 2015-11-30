#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"

class CompileGetArrayItem : public Compiler
{
public:
	CompileGetArrayItem();
	~CompileGetArrayItem();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileGetArrayItem(); };

private:
	string currArrayItemTempVar;
};

