#pragma once
#include "CompileOperator.h"

class CompileUserFunction :
	public Compiler
{
public:
	CompileUserFunction();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileUserFunction(); };
	~CompileUserFunction();
};

