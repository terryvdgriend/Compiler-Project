#pragma once
#include "Compiler.h"
#include "DirectFunctionCall.h"
#include "FunctionCall.h"
#include "CompileCondition.h"

class CompileSingleStatement : public Compiler
{
public:
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileSingleStatement(); };
};

