#pragma once
#include "Token.h"

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
