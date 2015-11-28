#pragma once
#include "LinkedActionList.h"
#include "LinkedList.h"

class Compute
{
	public:
		shared_ptr<LinkedActionList> computeCompile(LinkedList& tokenList);
		void checkNewCompile(LinkedList& tokenList, LinkedActionList& compiledList, shared_ptr<Token> token);
};