#pragma once
#include "Compiler.h"

class CompileOperator : Compiler
{
private:
	std::map<Token::iToken, string> tokenMap;
public:
	CompileOperator();
	void Compile(LinkedList& cTokenList, LinkedList& begin, LinkedList& end, LinkedActionList listActionNodes, ActionNode actionBefore);
	~CompileOperator();

protected:
	std::map<Token::iToken, string> getTokenMap();
};

