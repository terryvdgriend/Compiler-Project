#pragma once
#include "CompileOperator.h"

class CompileFunction : public CompileOperator
{
	public:
		CompileFunction();

		shared_ptr<Compiler> create();
};