#pragma once
#include "CompileOperator.h"
#include "DoNothingNode.h"
#include "TokenExpectation.h"
#include "FunctionHandler.h"

class CompileUserFunction :
	public Compiler
{
private:
	string _params;
	LinkedActionList* _body;
	std::string functionName;
public:
	CompileUserFunction();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	void CompileParams(LinkedList & cTokenList, Token & begin, Token & end);
	void CompileBody(LinkedList & cTokenList, Token & begin, Token & end, int Level);
	void ConnectList();
	Compiler * Create() { return new CompileUserFunction(); };
	~CompileUserFunction();
};

