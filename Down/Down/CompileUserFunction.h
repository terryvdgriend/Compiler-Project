#pragma once
#include "Compiler.h"

class CompileUserFunction : public Compiler
{
	public:
		CompileUserFunction();

		void compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
		shared_ptr<Compiler> create();

	private:
		string _params;
		string functionName;
		shared_ptr<LinkedList> _body;
		unique_ptr<vector<shared_ptr<Token>>> _paramTokens;
		shared_ptr<Token> _returnToken;

		void compileParams(LinkedList& cTokenList, Token& begin, Token& end);
		void compileBody(LinkedList& cTokenList, Token& begin, Token& end, int Level);
		void connectList();
};