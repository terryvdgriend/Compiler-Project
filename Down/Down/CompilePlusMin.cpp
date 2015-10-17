#include "stdafx.h"
#include "CompilePlusMin.h"


CompilePlusMin::CompilePlusMin()
{
	std::map<Token::iToken, string> tokenMap = getTokenMap();
	tokenMap[Token::PLUS] = "$+";
	tokenMap[Token::MINUS] = "$-";
}


CompilePlusMin::~CompilePlusMin()
{
}
