#pragma once
#include "CompileOperator.h"

class CompileComparison : public CompileOperator
{
	public:
		CompileComparison();

		shared_ptr<Compiler> create();
};