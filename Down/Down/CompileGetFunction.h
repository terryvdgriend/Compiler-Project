#pragma once
#include "Compiler.h"

class CompileGetFunction : public Compiler
{
	public:
		CompileGetFunction();

		void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);

	private:
		string _params;
		string _name;
		bool userDefined;
		vector<shared_ptr<Token>> _paramTokens;
		map<string, string> variableMap;
		shared_ptr<Token> _returnToken;
		shared_ptr<LinkedTokenList> _bodyTokens;
		shared_ptr<LinkedActionList> _compiledStatement;
		shared_ptr<LinkedActionList> _body;
		shared_ptr<LinkedActionList> _parameters;
		shared_ptr<LinkedActionList> _functionParams;
		shared_ptr<LinkedActionList> _functionCall;

		void compileNotUserDefined(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end);
		void compileUserDefined(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end);
		void changeVariables(const shared_ptr<LinkedTokenList>& tokenList);
		void changeVariable(shared_ptr<Token>& token);
		void connectParams(shared_ptr<Token> param, shared_ptr<LinkedTokenList>& paramlist);

		void connectLists();
};