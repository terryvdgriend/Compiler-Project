#pragma once
#include "LinkedList.h"
#include "LinkedActionList.h"
#include "ActionNode.h"

class Compiler
{
public:
	Compiler();
	virtual void  Compile(LinkedList& cTokenList, LinkedList& begin, LinkedList& end, LinkedActionList listActionNodes, ActionNode actionBefore) = 0;
	~Compiler();
};

