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
	std::vector<LinkedActionList*> _params;
	LinkedActionList* _body;
public:
	CompileGetFunction();
	void ConnectLists();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	void CompileParams(LinkedList& cTokenList, Token& begin, Token& end);

	Compiler * Create() { return new CompileGetFunction(); };
	~CompileGetFunction();
};

