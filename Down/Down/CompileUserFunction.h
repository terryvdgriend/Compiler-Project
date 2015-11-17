#pragma once
#include "CompileOperator.h"

class CompileUserFunction :
	public CompileOperator
{
public:
	CompileUserFunction();
	Compiler * Create() { return new CompileUserFunction(); };
	~CompileUserFunction();
};

