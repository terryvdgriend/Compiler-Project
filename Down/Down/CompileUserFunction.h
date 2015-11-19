#pragma once
#include "CompileOperator.h"
#include "DoNothingNode.h"
#include "TokenExpectation.h"

class CompileUserFunction :
	public Compiler
{
private:
	LinkedActionList* _compiledStatement;
	//LinkedActionList* _condition;
	LinkedActionList* _body;
public:
	CompileUserFunction();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileUserFunction(); };
	~CompileUserFunction();
};

