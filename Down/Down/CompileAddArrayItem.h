#pragma once
#include "Compiler.h"

class CompileAddArrayItem : public Compiler
{
	public:
		void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);
		
		string getCurrentArray();
		void setCurrentArray(string newCurrentArray);
		bool isFromArray();
		void setFromArray(bool newFromArray);
		int getFromArrayLength();
		void setFromArrayLength(int newFromArrayLength);

	private:
		string currentArray;
		string currentArrayTempVar;
		bool fromArray;
		int fromArrayLength;
};