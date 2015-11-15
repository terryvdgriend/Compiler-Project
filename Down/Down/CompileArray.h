#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"
#include "CompileOperator.h"

class CompileArray : public CompileOperator
{
public:
	CompileArray();
	~CompileArray();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileArray(); };

private:
	LinkedActionList* _compiledArray;
	LinkedActionList* _arrayBody;
	void connectList();
};

