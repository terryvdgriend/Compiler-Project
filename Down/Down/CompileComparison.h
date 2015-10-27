#pragma once
#include "CompileOperator.h"
class CompileComparison :
	public CompileOperator
{
public:
	CompileComparison();
	Compiler * Create() { return new CompileComparison(); };
	~CompileComparison();
};

