#pragma once
#include "Compiler.h"

class CompileLValue : Compiler
{
public:
	CompileLValue();
	virtual void Compile(LinkedList& cTokenList, LinkedList& begin, LinkedList& end, LinkedActionList listActionNodes, ActionNode actionBefore);
	~CompileLValue();
};

