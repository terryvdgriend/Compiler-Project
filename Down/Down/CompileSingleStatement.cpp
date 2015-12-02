#include "stdafx.h"
#include "CompileSingleStatement.h"

#define SET_ID_TO_RT  "IdentifierToReturnValue"
#define SET_CONST_TO_RT  "ConstantToReturnValue"
#define SET_GET_FROM_RT  "getFromReturnValue"

void CompileSingleStatement::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	switch (begin.getEnum())
	{
		case Token::IDENTIFIER:
		{
			Token* next = begin.next;
			DirectFunctionCall* directFunctionCall = nullptr;
			string sBuffer, saArguments[2];
			ActionNode* beforeFunction = nullptr;

			if (next != nullptr && next->getEnum() == Token::CONDITION_OPEN)
			{
				directFunctionCall = new DirectFunctionCall();
				saArguments[0] = begin.getText();
				saArguments[1] = getNextLocalVariableName(sBuffer);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_ID_TO_RT);
				directFunctionCall->setAt(1, saArguments[1].c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				CompileCondition condition;
				condition.Compile(cTokenList, *next->next, *next->getPartner(), listActionNodes, *beforeFunction);
			}
			else
			{
				saArguments[0] = SET_ID_TO_RT;
				saArguments[1] = begin.getText();

				directFunctionCall = new DirectFunctionCall;
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, saArguments[0].c_str());
				directFunctionCall->setAt(1, saArguments[1].c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);
			}
            
            break;
		}
		
		case Token::CONDITION_OPEN:
		{
			Token* next = &begin;
			CompileCondition condition;
			condition.Compile(cTokenList, *next->next, *next->getPartner(), listActionNodes, actionBefore);
            break;
		}
		case Token::FUNCTION_DECLARE_OPEN:
		{
			Token* next = &begin;
			CompileGetFunction function;
			function.Compile(cTokenList, *next, *next->getPartner(), listActionNodes, actionBefore);
			break;
		}
		case Token::NUMBER:
		case Token::TEXT:
		case Token::BOOL:
		{
			DirectFunctionCall* directFunctionCall = new DirectFunctionCall;
			directFunctionCall->setArraySize(2);
			directFunctionCall->setAt(0, SET_CONST_TO_RT);
			directFunctionCall->setAt(1, begin.getText().c_str());
			listActionNodes.insertBefore(&actionBefore, directFunctionCall);
            break;
		}
        default: {
            break;
        }
	}
}

CompileSingleStatement::CompileSingleStatement(){

}

CompileSingleStatement::~CompileSingleStatement(){
}

