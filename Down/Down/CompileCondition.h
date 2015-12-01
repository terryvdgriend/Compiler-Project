#pragma once
#include "CompileOperator.h"

class CompileCondition : public CompileOperator
{
	public:
		CompileCondition();

		shared_ptr<Compiler> create();
};