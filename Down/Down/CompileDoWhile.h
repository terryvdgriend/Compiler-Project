#pragma once
#include "Compiler.h"
class CompileDoWhile :
	public Compiler
{
private:
	LinkedActionList* _compiledStatement;
	LinkedActionList* _condition;
	LinkedActionList* _body;
	ActionNode* bodyNode;
public:
	CompileDoWhile();
	void ConnectLists();
	virtual void Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore);
	~CompileDoWhile();
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
