#pragma once
#include "Compiler.h"

class CompileSingleStatement : public Compiler
{
	public:
		void compile(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end, 
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);
		shared_ptr<Compiler> create();
};