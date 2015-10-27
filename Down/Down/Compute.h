#pragma once
#include "Token.h"
#include <list>
#include "LinkedActionList.h"
#include "LinkedList.h"

class Compute
{
public:
	Compute();
	LinkedActionList* ComputeCompile(LinkedList* lToken, LinkedActionList* lRun);
	void CheckNewCompile(LinkedList* lToken, LinkedActionList* lRun, Token* token);
	~Compute();
};

