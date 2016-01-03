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

		int *getFromMultiArrayLength();
		void setFromMultiArrayLength(int firstFromMultiArrayLength, int secondFromMultiArrayLength);

		void setMultiArray(bool newIsMultiDimensional) { isMultiDimensional = newIsMultiDimensional; };

		void setItemPositionInMultiArray(int firstItemPositionInMultiArray, int secondItemPositionInMultiArray);

	private:
		string currentArray;
		string currentArrayTempVar;
		bool fromArray;
		int fromArrayLength;

		int fromMultiArrayLength[2];
		bool isMultiDimensional;
		int itemPositionInMultiArray[2];
};