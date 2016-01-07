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

		vector<int>getFromMultiArrayLength();
		void setFromMultiArrayLength(vector<int> setIndexFromMulti);

		void setItemPositionInMultiArray(vector<int> PositionInMultiArray);

		void setMultiArray(bool newIsMultiDimensional) { isMultiDimensional = newIsMultiDimensional; };

		void createNewLineToken(shared_ptr<LinkedTokenList>& param, vector<shared_ptr<LinkedTokenList>>& list);

	private:
		string currentArray = "";
		string currentArrayTempVar = "";
		bool fromArray = false;
		int fromArrayLength = 0;

		vector<int> fromMultiArrayLength;
		bool isMultiDimensional = false;
		vector<int> itemPositionInMultiArray;
};