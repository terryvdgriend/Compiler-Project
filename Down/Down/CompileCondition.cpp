#include "stdafx.h"
#include "CompileCondition.h"
#include "CompilePlusMinus.h"

CompileCondition::CompileCondition(): CompileOperator(new CompilePlusMinus)
{
	std::map<Token::iToken, string> tokenMap = getTokenMap();
	tokenMap[Token::LARGER_THAN] = "$>";
	tokenMap[Token::LESS_THAN] = "$<";
	tokenMap[Token::EQUALS_TO] = "$==";
	//tokenMap[Token::EQUALS] = "$!="; TODO: NotEqualTo
}


CompileCondition::~CompileCondition()
{
}