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
	LinkedActionList* _functionParams;
	LinkedActionList* _functionCall;
	bool userdef;
public:
	CompileGetFunction();
	void ConnectLists();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	void CompileNotUserDefined(LinkedList& cTokenList, Token& begin, Token& end);
	void CompileUserDefined(LinkedList & cTokenList, Token & begin, Token & end);
	Compiler * Create() { return new CompileGetFunction(); };


	~CompileGetFunction();
};

