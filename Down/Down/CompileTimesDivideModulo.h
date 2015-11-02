#pragma once
#include "CompileOperator.h"

class CompileTimesDivideModulo : public CompileOperator
{
	public:
		CompileTimesDivideModulo();
		Compiler * Create() { return new CompileTimesDivideModulo(); };
		~CompileTimesDivideModulo();
};