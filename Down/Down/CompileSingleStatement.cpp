#include "stdafx.h"
#include "CompileSingleStatement.h"
#include "CompileGetFunction.h"
#include "DirectFunctionCall.h"

#define SET_ID_TO_RT "IdentifierToReturnValue"
#define SET_CONST_TO_RT "ConstantToReturnValue"
#define SET_GET_FROM_RT "getFromReturnValue"

void CompileSingleStatement::compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	switch (begin.getEnum())
	{
		case Token::IDENTIFIER:
		{
			shared_ptr<Token> next = make_shared<Token>(begin.next); // Todo fix tokenizer, will throw error soon
			shared_ptr<DirectFunctionCall> directFunctionCall = nullptr;
			string sBuffer, saArguments[2];
			shared_ptr<ActionNode> beforeFunction = nullptr;

			if (next != nullptr && next->getEnum() == Token::CONDITION_OPEN)
			{
				directFunctionCall = make_shared<DirectFunctionCall>();
				saArguments[0] = begin.getText();
				saArguments[1] = getNextLocalVariableName(sBuffer);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_ID_TO_RT);
				directFunctionCall->setAt(1, saArguments[1].c_str());
				listActionNodes.insertBefore(make_shared<ActionNode>(actionBefore), directFunctionCall);

				shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
				condition->compile(cTokenList, *next->next, *next->getPartner(), listActionNodes, *beforeFunction);
			}
			else
			{
				saArguments[0] = SET_ID_TO_RT;
				saArguments[1] = begin.getText();

				directFunctionCall = make_shared<DirectFunctionCall>();
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, saArguments[0].c_str());
				directFunctionCall->setAt(1, saArguments[1].c_str());
				listActionNodes.insertBefore(make_shared<ActionNode>(actionBefore), directFunctionCall);
			}
            
            break;
		}
		case Token::CONDITION_OPEN:
		{
			shared_ptr<Token> next = make_shared<Token>(begin);
			shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
			condition->compile(cTokenList, *next->next, *next->getPartner(), listActionNodes, actionBefore);

            break;
		}
		case Token::FUNCTION_DECLARE_OPEN:
		{
			shared_ptr<Token> next = make_shared<Token>(begin);
			shared_ptr<CompileGetFunction> function = make_shared<CompileGetFunction>();
			function->compile(cTokenList, *next, *next->getPartner()->getPartner()->getPartner(), listActionNodes, actionBefore);

			break;
		}
		case Token::NUMBER:
		case Token::TEXT:
		case Token::BOOL:
		{
			shared_ptr<DirectFunctionCall> directFunctionCall = shared_ptr<DirectFunctionCall>();
			directFunctionCall->setArraySize(2);
			directFunctionCall->setAt(0, SET_CONST_TO_RT);
			directFunctionCall->setAt(1, begin.getText().c_str());
			listActionNodes.insertBefore(make_shared<ActionNode>(actionBefore), directFunctionCall);

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