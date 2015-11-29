#pragma once
#include "Compiler.h"
#include "TokenExpectation.h"
#include "FunctionHandler.h"
#include "CompilerHeader.h"
#include <vector>
class CompileGetFunction :
	public Compiler
{
private:
	LinkedActionList* _compiledStatement;
	std::string _params;
	std::string _name;
	LinkedActionList* _body;
	Token* _returnToken;
	LinkedList* _bodyTokens;
	std::vector<Token*> _paramTokens;
	LinkedActionList* _parameters;
	LinkedActionList* _functionParams;
	LinkedActionList* _functionCall;
	std::map<string, string> variableMap;
	bool userdef;
public:
	CompileGetFunction();
	void ConnectLists();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	void CompileNotUserDefined(LinkedList& cTokenList, Token& begin, Token& end);
	void CompileUserDefined(LinkedList & cTokenList, Token & begin, Token & end);
	void ChangeVariables(LinkedList & list);
	void ChangeVariable(Token & token);
	void ConnectParams(Token * param, LinkedList& paramlist);
	Compiler * Create() { return new CompileGetFunction(); };


	~CompileGetFunction();
};

