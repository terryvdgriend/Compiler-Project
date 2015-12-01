#pragma once
#include "ActionNode.h"
#include "Token.h"

class CompileNextLevel
{
	public:
		CompileNextLevel();
		
		shared_ptr<Token> getBegin();
		void setBegin(shared_ptr<Token>& value);
		shared_ptr<Token> getEnd();
		void setEnd(shared_ptr<Token>& value);
		shared_ptr<ActionNode> getBefore();
		void setBefore(shared_ptr<ActionNode>& value);

	private:
		shared_ptr<Token> begin;
		shared_ptr<Token> end;
		shared_ptr<ActionNode> before;
};