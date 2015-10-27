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
	void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	Compiler * Create() { return new CompileOperator(); };
	~CompileOperator();


protected:
	std::map<Token::iToken, string> getTokenMap();
};

