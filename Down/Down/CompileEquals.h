#pragma once
#include "CompileOperator.h"

class CompileEquals : public CompileOperator
{
	public:
		CompileEquals();

		shared_ptr<Compiler> create();
};