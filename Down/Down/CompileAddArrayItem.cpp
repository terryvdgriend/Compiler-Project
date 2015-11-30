#include "stdafx.h"
#include "CompileAddArrayItem.h"

#include "CompileEquals.h"

#include "ConditionalJumpNode.h"
#include "JumpGotoNode.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"
#include "TokenExpectation.h"
#include "CompileSingleStatement.h"

#define SET_ID_TO_RT "IdentifierToReturnValue"
#define SET_CONST_TO_RT "ConstantToReturnValue"
#define SET_GET_FROM_RT "getFromReturnValue"

CompileAddArrayItem::CompileAddArrayItem()
{
}

CompileAddArrayItem::~CompileAddArrayItem()
{
}

void CompileAddArrayItem::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	Token* current = &begin;
	int arrayLevel = begin.getLevel();

	list<TokenExpectation> expected = list<TokenExpectation>();
	expected.push_back(TokenExpectation(arrayLevel, Token::IDENTIFIER));
	expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_OPEN));
	expected.push_back(TokenExpectation(arrayLevel + 1, Token::NUMBER));
	expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_CLOSE));
	expected.push_back(TokenExpectation(arrayLevel, Token::EQUALS));

	Token* temp = &begin;

	while (temp->next != nullptr)
	{
		if (temp->getEnum() == Token::IDENTIFIER && (temp->getSub() == Token::TYPE_NUMBER_ARRAY || temp->getSub() == Token::TYPE_TEXT_ARRAY || temp->getSub() == Token::TYPE_FACT_ARRAY))
		{
			if (temp->getSub() == Token::TYPE_NUMBER_ARRAY) { expected.push_back(TokenExpectation(arrayLevel, Token::NUMBER)); }
			else if (temp->getSub() == Token::TYPE_TEXT_ARRAY) { expected.push_back(TokenExpectation(arrayLevel, Token::TEXT)); }
			else if (temp->getSub() == Token::TYPE_FACT_ARRAY) { expected.push_back(TokenExpectation(arrayLevel, Token::FACT)); }
			break;
		}
		temp = temp->next;
	}

	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE)
		{
			if (current->next != nullptr)
			{
				current = current->next;
			}
			else
			{
				break;
			}
		}

		if (current == nullptr) {
			ErrorHandler::getInstance()->addError(Error{ "set an item not completed", ".md",-1, -1, Error::error });
			begin = end;
			break;
		}

		string sBuffer;

		if (expectation.Level == arrayLevel)
		{
			if (current->getEnum() != expectation.TokenType) {
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, current->getEnum());
				begin = end;
				break;
			}

			if (current->getEnum() == Token::IDENTIFIER)
			{
				DirectFunctionCall* directFunctionCall = new DirectFunctionCall;
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_ID_TO_RT);
				directFunctionCall->setAt(1, current->getText().c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				directFunctionCall = new DirectFunctionCall;
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				currArrayTempVar = getCurrentLocalVariableName();
			}
			else if (current->getEnum() == Token::NUMBER || current->getEnum() == Token::TEXT || current->getEnum() == Token::FACT)
			{
				DirectFunctionCall* directFunctionCall = new DirectFunctionCall;
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_CONST_TO_RT);
				directFunctionCall->setAt(1, current->getText().c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				directFunctionCall = new DirectFunctionCall;
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				string saArguments[4];

				string tempCurrentLocalVariable = getCurrentLocalVariableName();

				saArguments[0] = "$AddItemToArrayAt";
				saArguments[1] = currArrayTempVar;
				saArguments[2] = getPreviousLocalVariableName(sBuffer);
				saArguments[3] = tempCurrentLocalVariable;

				FunctionCall* pFunction = new FunctionCall();
				pFunction->setArraySize(4);
				for (int n = 0; n < 4; n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				listActionNodes.insertBefore(&actionBefore, pFunction);
			}

			current = current->next;
		}
		else if (expectation.Level >= arrayLevel)
		{
			Token* prev = current->previous;
			while (prev->getEnum() != Token::ARRAY_OPEN)
			{
				prev = prev->previous;
			}
			prev = prev->getPartner();

			DirectFunctionCall* directFunctionCall = new DirectFunctionCall;
			directFunctionCall->setArraySize(2);
			directFunctionCall->setAt(0, SET_CONST_TO_RT);
			directFunctionCall->setAt(1, current->getText().c_str());
			listActionNodes.insertBefore(&actionBefore, directFunctionCall);

			directFunctionCall = new DirectFunctionCall;
			directFunctionCall->setArraySize(2);
			directFunctionCall->setAt(0, SET_GET_FROM_RT);
			directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
			listActionNodes.insertBefore(&actionBefore, directFunctionCall);

			current = current->next;
		}
	}

	begin = *current;
}