#include "stdafx.h"
#include "CompileCondition.h"
#include "CompileUnary.h"

CompileCondition::CompileCondition() : CompileOperator(make_shared<CompileUnary>())
{
	tokenMap[IToken::LARGER_THAN]		= "$>";
	tokenMap[IToken::LESS_THAN]			= "$<";
	tokenMap[IToken::LARGER_LIKE_THAN]	= "$>=";
	tokenMap[IToken::LESS_LIKE_THAN]	= "$<=";
	tokenMap[IToken::EQUALS_TO]			= "$==";
}