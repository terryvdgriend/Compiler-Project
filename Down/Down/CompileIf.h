#pragma once
#include "Compiler.h"

class CompileIf : Compiler
{
public:
	CompileIf();
	virtual void Compile(LinkedList& cTokenList, LinkedList& begin, LinkedList& end, LinkedActionList listActionNodes, ActionNode actionBefore);
	~CompileIf();
};

