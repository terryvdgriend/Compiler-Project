#pragma once
#include "CompileOperator.h"

class CompilePlusMinus : public CompileOperator
{
	public:
		CompilePlusMinus();
		Compiler * Create() { return new CompilePlusMinus(); };
		~CompilePlusMinus();
};