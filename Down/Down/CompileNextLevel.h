#pragma once
#include "ActionNode.h"
#include "Token.h"

class CompileNextLevel
{
	public:
		CompileNextLevel();
		
		shared_ptr<Token> getBegin();
		shared_ptr<Token> getEnd();
		shared_ptr<ActionNode> getBefore();

	private:
		shared_ptr<Token> begin;
		shared_ptr<Token> end;
		shared_ptr<ActionNode> before;
};