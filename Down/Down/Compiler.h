#pragma once
#include "LinkedList.h"
#include "LinkedActionList.h"
#include "ActionNode.h"

class Compiler
{
public:
	//Compiler();
	virtual void  Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore) = 0;
	virtual Compiler * Create() = 0;
	int asd = 10;
	std::string getNextLocalVariableName(std::string& buffer);
};

