#include "stdafx.h"
#include "CompileSingleStatement.h"
#include "CompileCondition.h"
#include "CompileGetArrayItem.h"
#include "CompileGetFunction.h"
#include "DirectFunctionCall.h"

#define SET_ID_TO_RT "IdentifierToReturnValue"
#define SET_CONST_TO_RT "ConstantToReturnValue"
#define SET_GET_FROM_RT "getFromReturnValue"

void CompileSingleStatement::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
									 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	switch (begin->getType())
	{
		case IToken::IDENTIFIER:
		{
			shared_ptr<Token> next = begin->getNext();
			shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(make_shared<Token>(begin));
			shared_ptr<ActionNode> beforeFunction = nullptr;
			string sBuffer, saArguments[2];
			
			if (next != nullptr && next->getType() == IToken::ARRAY_OPEN) 
			{
				CompileGetArrayItem arrayitem;
				arrayitem.compile(tokenList, begin, end, listActionNodes, actionBefore);

			}
			else if (next != nullptr && next->getType() == IToken::CONDITION_OPEN)
			{
				saArguments[0] = begin->getText();
				saArguments[1] = getNextLocalVariableName(sBuffer);

				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_ID_TO_RT);
				directFunctionCall->setAt(1, saArguments[1].c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				CompileCondition condition;
				condition.compile(tokenList, next->getNext(), next->getPartner(), listActionNodes, beforeFunction);
			}
			else
			{
				saArguments[0] = SET_ID_TO_RT;
				saArguments[1] = begin->getText();

				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, saArguments[0].c_str());
				directFunctionCall->setAt(1, saArguments[1].c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);
			}
            
            break;
		}
		case IToken::CONDITION_OPEN:
		{
			shared_ptr<Token> next = begin;
			CompileCondition condition;
			condition.compile(tokenList, next->getNext(), next->getPartner(), listActionNodes, actionBefore);

            break;
		}
		case IToken::FUNCTION_DECLARE_OPEN:
		{
			shared_ptr<Token> next = begin;
			CompileGetFunction function;
			function.compile(tokenList, next, next->getPartner(), listActionNodes, actionBefore);

			break;
		}
		case IToken::NUMBER:
		case IToken::TEXT:
		case IToken::FACT:
		{
			shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(make_shared<Token>(begin));
			directFunctionCall->setArraySize(2);
			directFunctionCall->setAt(0, SET_CONST_TO_RT);
			directFunctionCall->setAt(1, begin->getText().c_str());
			listActionNodes->insertBefore(actionBefore, directFunctionCall);

            break;
		}
        default: 
		{
            break;
        }
	}
}