#pragma once
#include "CompileOperator.h"

class CompilePlusMinus : public CompileOperator
{
	public:
		CompilePlusMinus();

		shared_ptr<Compiler> create();
};