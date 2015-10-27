#pragma once
#include "CompileOperator.h"
class CompileFunction :
	public CompileOperator
{
public:
	CompileFunction();
	Compiler * Create() { return new CompileFunction(); };
	~CompileFunction();
};

