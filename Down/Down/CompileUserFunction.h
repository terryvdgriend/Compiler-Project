#pragma once
#include "CompileOperator.h"
#include "DoNothingNode.h"
#include "TokenExpectation.h"

class CompileUserFunction :
	public Compiler
{
private:
	LinkedActionList* _compiledStatement;
	std::vector<LinkedActionList>* _params;
	LinkedActionList* _body;
	std::string functionName;
public:
	CompileUserFunction();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	void CompileParams(LinkedList & cTokenList, Token & begin, Token & end);
	void CompileBody(LinkedList & cTokenList, Token & begin, Token & end, int Level);
	Compiler * Create() { return new CompileUserFunction(); };
	~CompileUserFunction();
};

