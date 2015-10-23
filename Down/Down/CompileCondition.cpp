#include "stdafx.h"
#include "CompileCondition.h"

#include "CompilePlusMin.h"

CompileCondition::CompileCondition()
	: CompileOperator(new CompilePlusMin)
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
