#include "stdafx.h"
#include "CompileCondition.h"
#include "CompileSingleStatement.h"
#include "CompileGetFunction.h"
#include "DirectFunctionCall.h"

#define SET_ID_TO_RT "IdentifierToReturnValue"
#define SET_CONST_TO_RT "ConstantToReturnValue"
#define SET_GET_FROM_RT "getFromReturnValue"

void CompileSingleStatement::compile(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
									 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	switch (begin->getType())
	{
		case IToken::IDENTIFIER:
		{
			shared_ptr<Token> next = begin->getNext();
			shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>();
			string sBuffer, saArguments[2];
			shared_ptr<ActionNode> beforeFunction = nullptr;

			if (next != nullptr && next->getType() == IToken::CONDITION_OPEN)
			{
				saArguments[0] = begin->getText();
				saArguments[1] = getNextLocalVariableName(sBuffer);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_ID_TO_RT);
				directFunctionCall->setAt(1, saArguments[1].c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
				condition->compile(tokenList, next->getNext(), next->getPartner(), listActionNodes, beforeFunction);
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
			shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
			condition->compile(tokenList, next->getNext(), next->getPartner(), listActionNodes, actionBefore);

            break;
		}
		case IToken::FUNCTION_DECLARE_OPEN:
		{
			shared_ptr<Token> next = begin;
			shared_ptr<CompileGetFunction> function = make_shared<CompileGetFunction>();
			function->compile(tokenList, next, next->getPartner(), listActionNodes, actionBefore);

			break;
		}
		case IToken::NUMBER:
		case IToken::TEXT:
		case IToken::BOOL:
		{
			shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>();
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

shared_ptr<Compiler> CompileSingleStatement::create()
{
	return make_shared<CompileSingleStatement>();
}