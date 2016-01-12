#pragma once
#include "Compiler.h"

struct Param {
	vector<int> paramIndexes;
	shared_ptr<LinkedTokenList> params;
	Param() {
		params = make_shared<LinkedTokenList>();
	}
};

class CompileArray : public Compiler
{
	public:
		void compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
					 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore);

	private:
		string currentArrayTempVar;
		string previousArrayTempVar;
		int filledLength;
		vector<int> filledMultiLength;
		vector<string> multiParam;

		bool isArrayLengthFilled;

		void createNewLineToken(shared_ptr<Param>& param, vector<shared_ptr<Param>>& list);

		bool executeArrayItems(shared_ptr<LinkedActionList> &listActionNodes, shared_ptr<LinkedTokenList> tokenList, shared_ptr<ActionNode> &actionBefore, shared_ptr<Token> &current, string sBuffer, int countOfRows, bool isMultiDimensional);
};