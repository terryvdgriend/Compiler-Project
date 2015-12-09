#include "stdafx.h"
#include "CompileCondition.h"
#include "CompileUnary.h"

CompileCondition::CompileCondition(): CompileOperator(new CompileUnary)
{
	TokenMap &tokenMap = getTokenMap();
	tokenMap[Token::LARGER_THAN] = "$>";
	tokenMap[Token::LESS_THAN] = "$<";
	tokenMap[Token::LARGER_LIKE_THAN] = "$>=";
	tokenMap[Token::LESS_LIKE_THAN] = "$<=";
	tokenMap[Token::EQUALS_TO] = "$==";
	//tokenMap[Token::EQUALS] = "$!="; TODO: NotEqualTo
}


CompileCondition::~CompileCondition()
{
}
