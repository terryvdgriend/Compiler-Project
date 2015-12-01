#pragma once
#include "CompileOperator.h"

class CompileTimesDivideModulo : public CompileOperator
{
	public:
		CompileTimesDivideModulo();

		shared_ptr<Compiler> create();
};