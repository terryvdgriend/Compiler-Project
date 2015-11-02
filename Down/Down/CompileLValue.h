#pragma once
#include "Compiler.h"

class CompileLValue : public Compiler
{
public:
	CompileLValue();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileLValue(); };
	~CompileLValue();
};

