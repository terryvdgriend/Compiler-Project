#pragma once
#include "Token.h"
#include "LinkedActionList.h"
#include "LinkedList.h"

class Compute
{
	public:
		Compute();
		shared_ptr<LinkedActionList> computeCompile(LinkedList* lToken);
		void checkNewCompile(LinkedList* lToken, shared_ptr<LinkedActionList> lRun, Token* token);
};