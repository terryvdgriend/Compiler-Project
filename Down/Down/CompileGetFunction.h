#pragma once
#include "Compiler.h"

class CompileGetFunction : public Compiler
{
	public:
		CompileGetFunction();

		void compile(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end, 
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);
		shared_ptr<Compiler> create();

	private:
		string _params;
		string _name;
		bool userDefined;
		vector<shared_ptr<Token>> _paramTokens;
		map<string, string> variableMap;
		shared_ptr<Token> _returnToken;
		shared_ptr<LinkedList> _bodyTokens;
		shared_ptr<LinkedActionList> _compiledStatement;
		shared_ptr<LinkedActionList> _body;
		shared_ptr<LinkedActionList> _parameters;
		shared_ptr<LinkedActionList> _functionParams;
		shared_ptr<LinkedActionList> _functionCall;

		void compileNotUserDefined(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end);
		void compileUserDefined(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end);
		void changeVariables(shared_ptr<LinkedList>& list);
		void changeVariable(shared_ptr<Token>& token);
		void connectParams(shared_ptr<Token> param, shared_ptr<LinkedList>& paramlist);

		void connectLists();
};