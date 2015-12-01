#pragma once
#include "CompileOperator.h"

class CompileUnary : public CompileOperator
{
	public:
		CompileUnary();

		shared_ptr<Compiler> create();
};