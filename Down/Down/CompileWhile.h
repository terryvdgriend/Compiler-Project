#pragma once
#include "Compiler.h"

class CompileWhile : Compiler
{
public:
	CompileWhile();
	virtual void Compile(LinkedList& cTokenList, LinkedList& begin, LinkedList& end, LinkedActionList listActionNodes, ActionNode actionBefore);
	~CompileWhile();
};

