#pragma once
#include "Compiler.h"

class CompileUserFunction : public Compiler
{
	public:
		CompileUserFunction();

		void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);
		shared_ptr<Compiler> create();

	private:
		string _params;
		string functionName;
		shared_ptr<LinkedTokenList> _body;
		vector<shared_ptr<Token>> _paramTokens;
		shared_ptr<Token> _returnToken;

		void compileParams(shared_ptr<Token>& begin, shared_ptr<Token>& end);
		void compileBody(shared_ptr<Token>& begin, shared_ptr<Token>& end);
		void connectList();
};