#pragma once
#include "ActionNode.h"
#include "Token.h"

class CompileNextLevel
{
	public:
		CompileNextLevel();
		
		shared_ptr<Token> getBegin();
		void setBegin(shared_ptr<Token>& begin);
		shared_ptr<Token> getEnd();
		void setEnd(shared_ptr<Token>& end);
		shared_ptr<ActionNode> getBefore();
		void setBefore(shared_ptr<ActionNode>& before);

	private:
		shared_ptr<Token> _begin;
		shared_ptr<Token> _end;
		shared_ptr<ActionNode> _before;
};