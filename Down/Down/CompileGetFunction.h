#pragma once
#include "Compiler.h"
#include "CompilerHeader.h"
#include "FunctionHandler.h"
#include "TokenExpectation.h"

class CompileGetFunction : public Compiler
{
	public:
		CompileGetFunction();

		void compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
		void compileNotUserDefined(LinkedList& cTokenList, Token& begin, Token& end);
		void compileUserDefined(LinkedList& cTokenList, Token& begin, Token& end);
		void changeVariables(LinkedList& list);
		void changeVariable(Token& token);
		void connectParams(shared_ptr<Token> param, LinkedList& paramlist);
		shared_ptr<Compiler> create();

	private:
		string _params;
		string _name;
		bool userDefined;
		shared_ptr<vector<shared_ptr<Token>>> _paramTokens;
		unique_ptr<map<string, string>> variableMap;
		shared_ptr<Token> _returnToken;
		shared_ptr<LinkedList> _bodyTokens;
		shared_ptr<LinkedActionList> _compiledStatement;
		shared_ptr<LinkedActionList> _body;
		shared_ptr<LinkedActionList> _parameters;
		shared_ptr<LinkedActionList> _functionParams;
		shared_ptr<LinkedActionList> _functionCall;

		void connectLists();
};