#pragma once
#include "LinkedList.h"
#include "LinkedActionList.h"
#include "ActionNode.h"

class Compiler
{
public:
	virtual void Compile(LinkedList& tokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& before) = 0;
	std::string getNextLocalVariableName(std::string& buffer);
	virtual Compiler* Create() = 0;
	Token* Current = nullptr;
};

