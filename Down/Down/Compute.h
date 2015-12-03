#pragma once
#include "LinkedActionList.h"
#include "LinkedList.h"

class Compute
{
	public:
		shared_ptr<LinkedActionList> computeCompile(shared_ptr<LinkedList>& tokenList);
		void checkNewCompile(shared_ptr<LinkedList>& tokenList, shared_ptr<LinkedActionList>& compiledList, shared_ptr<Token> token);
};