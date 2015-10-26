#pragma once
#include "Compiler.h"

class CompileWhile : Compiler
{
private:
	LinkedActionList* _compiledStatement;
	LinkedActionList* _condition;
	LinkedActionList* _body;
public:
	CompileWhile();
	void ConnectLists();
	virtual void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	~CompileWhile();
};


struct TokenExpectation
{
public:
	int Level;
public:
	Token::iToken TokenType;

public:
	TokenExpectation(int level, Token::iToken tokenType)
	{
		Level = level;
		TokenType = tokenType;
	}

};
