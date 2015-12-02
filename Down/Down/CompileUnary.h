#pragma once
#include "CompileOperator.h"

class CompileUnary : public CompileOperator
{
public:
	CompileUnary();
	Compiler * Create() { return new CompileUnary(); };
	~CompileUnary();
};