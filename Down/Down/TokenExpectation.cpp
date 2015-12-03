#include "stdafx.h"
#include "TokenExpectation.h"

TokenExpectation::TokenExpectation(int level, IToken tokenType)
{
	_level		= level;
	_tokenType	= tokenType;
}

int TokenExpectation::getLevel()
{
	return _level;
}

void TokenExpectation::setLevel(int level)
{
	_level = level;
}

IToken TokenExpectation::getTokenType()
{
	return _tokenType;
}

void TokenExpectation::setTokenType(IToken tokenType)
{
	_tokenType = tokenType;
}