#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"

class CompileArray : public Compiler
{
public:
	CompileArray();
	~CompileArray();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileArray(); };

private:
	string currArrayTempVar;
	string prevArrayTempVar;
};

