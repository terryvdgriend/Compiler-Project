#pragma once
#include "Compiler.h"
#include "CompileNextLevel.h"

class CompileAddArrayItem : public Compiler
{
public:
	CompileAddArrayItem();
	~CompileAddArrayItem();
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileAddArrayItem(); };

	bool isFromArray() { return fromArray; }
	void setFromArray(bool newFromArray) { fromArray = newFromArray; }

	int getFromArrayLength() { return fromArrayLength; }
	void setFromArrayLength(int newFromArrayLength) { fromArrayLength = newFromArrayLength; }

	string getCurrentArray() { return currArray; }
	void setCurrentArray(string newCurrArray) { currArray = newCurrArray; }

private:
	string currArrayTempVar;

	bool fromArray;
	int fromArrayLength;

	string currArray;
};