#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"

class CompileAddArrayItem : public Compiler
{
public:
	CompileAddArrayItem();
	~CompileAddArrayItem();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileAddArrayItem(); };

private:
	string currArrayTempVar;
};