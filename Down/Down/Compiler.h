#pragma once
#include "LinkedActionList.h"
#include "LinkedTokenList.h"

class Compiler
{
	public:
		Compiler();

		virtual void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
							 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore) = 0;
		virtual shared_ptr<Compiler> create() = 0;

		string getNextLocalVariableName(string& buffer);
		shared_ptr<Token> getCurrentToken();
		void setCurrentToken(shared_ptr<Token>& nextToken);

	private:
		shared_ptr<Token> currentToken;
};