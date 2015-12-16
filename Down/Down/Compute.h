#pragma once
#include "LinkedActionList.h"
#include "LinkedTokenList.h"

class Compute
{
	public:
		shared_ptr<LinkedActionList> computeCompile(const shared_ptr<LinkedTokenList>& tokenList);
		void checkNewCompile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<LinkedActionList>& compiledList, shared_ptr<Token> token);
};