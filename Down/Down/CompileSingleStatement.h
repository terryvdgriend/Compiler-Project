#pragma once
#include "Compiler.h"

class CompileSingleStatement : public Compiler
{
	public:
		void compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
		shared_ptr<Compiler> create();
};