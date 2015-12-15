#pragma once
#include "Token.h"

struct TokenExpectation
{
	public:
		TokenExpectation(int level, IToken tokenType);

		int getLevel();
		void setLevel(int level);
		IToken getTokenType();
		void setTokenType(IToken tokenType);

	private:
		int _level;
		IToken _tokenType;
};