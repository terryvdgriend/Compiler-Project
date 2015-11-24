#pragma once
#include "Token.h"

struct TokenExpectation
{
public:
	int Level;
	Token::iToken TokenType;
public:
	
	TokenExpectation(int level, Token::iToken tokenType)
	{
		Level = level;
		TokenType = tokenType;
	};
	int getLevel() { return Level; };
	Token::iToken getTokenType() { return TokenType; };

};
