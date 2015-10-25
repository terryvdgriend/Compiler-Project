#pragma once
#include "Compiler.h"

class CompileSingleStatement : public Compiler
{
public:
	CompileSingleStatement();
	virtual void Compile(LinkedList& cTokenList, LinkedList& begin, LinkedList& end, LinkedActionList listActionNodes, ActionNode actionBefore);
	~CompileSingleStatement();
};

