#pragma once
#include "Compiler.h"

class CompileArray : public Compiler
{
	public:
		void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);

	private:
		string currentArrayTempVar;
		string previousArrayTempVar;
		int filledLength;
		int filledMultiLength[2];
		vector<string> multiParam;

		bool isArrayLengthFilled;

		void createNewLineToken(shared_ptr<LinkedTokenList>& param, vector<shared_ptr<LinkedTokenList>>& list);

		bool CompileArray::executeArrayItems(shared_ptr<LinkedActionList> &listActionNodes, shared_ptr<LinkedTokenList> tokenList, shared_ptr<ActionNode> &actionBefore, shared_ptr<Token> &current, string sBuffer, int countOfRows, bool isMultiDimensional);
};