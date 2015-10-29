#pragma once
#include "CompileOperator.h"
class CompileEquals :
	public CompileOperator
{
public:
	CompileEquals();
	Compiler * Create() { return new CompileEquals(); };
	~CompileEquals();
};

