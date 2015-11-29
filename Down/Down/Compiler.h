#pragma once
#include "ActionNode.h"
#include "LinkedActionList.h"
#include "LinkedList.h"

class Compiler
{
	public:
		virtual void compile(LinkedList& tokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& before) = 0;
		virtual shared_ptr<Compiler> create() = 0;

		string getNextLocalVariableName(string& buffer);
		shared_ptr<Token> getCurrentToken();
		void setCurrentToken(Token& nextToken);

	private:
		shared_ptr<Token> currentToken = nullptr;
};