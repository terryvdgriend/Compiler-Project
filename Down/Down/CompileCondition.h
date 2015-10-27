#pragma once
#include "CompileOperator.h"
class CompileCondition :
	public CompileOperator
{
public:
	CompileCondition();
	Compiler * Create() { return new CompileCondition(); };
	~CompileCondition();
};

