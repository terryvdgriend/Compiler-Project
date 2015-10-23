#pragma once
#include "Compiler.h"

class CompileOperator : public	Compiler
{
private:
	std::map<Token::iToken, string> tokenMap;
	Compiler *pNextLevel;
public:
	CompileOperator(Compiler* pNext);
	CompileOperator();
	void Compile(LinkedList& cTokenList, LinkedList& begin, LinkedList& end, LinkedActionList listActionNodes, ActionNode actionBefore);
	~CompileOperator();

protected:
	std::map<Token::iToken, string> getTokenMap();
};

