#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"

class CompileArrayItem : public Compiler
{
public:
	CompileArrayItem();
	~CompileArrayItem();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileArrayItem(); };

private:
	string currArrayItemTempVar;
};

