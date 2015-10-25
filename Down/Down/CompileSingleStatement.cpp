#include "stdafx.h"
#include "CompileSingleStatement.h"

const std::string CompileSingleStatement::SET_ID_TO_RT = "IdentifierToReturnValue";
const std::string CompileSingleStatement::SET_CONST_TO_RT = "ConstantToReturnValue";
const std::string CompileSingleStatement::SET_GET_FROM_RT = "getFromReturnValue";


CompileSingleStatement::CompileSingleStatement()
{
}

void CompileSingleStatement::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList listActionNodes, ActionNode actionBefore)
{
	switch (begin.getEnum())
	{
		case Token::IDENTIFIER:
		{
			
		}
		break;
		case Token::CONDITION_OPEN:
		{

		}
		case Token::NUMBER:
		case Token::TEXT:
		case Token::BOOL:
		{
			DirectFunctionCall* directFunctionCall = new DirectFunctionCall();
			directFunctionCall->setArraySize(2);
			directFunctionCall->setAt(0, SET_CONST_TO_RT.c_str());
			directFunctionCall->setAt(1, begin.getText().c_str());
			
		}
		break;
	}
}

CompileSingleStatement::~CompileSingleStatement()
{
}
