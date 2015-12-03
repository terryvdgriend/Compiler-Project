#include "stdafx.h"
#include "CompileAddArrayItem.h"

#include "CompilePlusMinus.h"
#include "CompileSingleStatement.h"
#include "TokenExpectation.h"

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
	if (!fromArray)
	{
		expected.push_back(TokenExpectation(arrayLevel, Token::IDENTIFIER));
		expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_OPEN));
		expected.push_back(TokenExpectation(arrayLevel + 1, Token::NUMBER));
		expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_CLOSE));
		expected.push_back(TokenExpectation(arrayLevel, Token::EQUALS));
		expected.push_back(TokenExpectation(arrayLevel, Token::ANY));
	}
	else
	{
		expected.push_back(TokenExpectation(arrayLevel, Token::ANY));
	}

	Token* temp = &begin;

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

		if (current->getLineNumber() > 20)
		{
			cout << "";
		}

		if (expectation.Level == arrayLevel)
		{
			if (expectation.getTokenType() != Token::ANY && current->getEnum() != expectation.TokenType) {
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, current->getEnum());
				begin = end;
				break;
			}

			if (expectation.getTokenType() == Token::ANY)
			{
				CompileCondition* compiledBodyPart = new CompileCondition();

				Token* seperator = current;
				while (seperator->getEnum() == Token::NEWLINE) {
					if (seperator->getEnum() != Token::NEWLINE) { break; }
					seperator = seperator->next;
				}

				string tempPreviousLocalVariable, tempCurrentLocalVariable;

				if (fromArray)
				{
					DirectFunctionCall* directFunctionCall = new DirectFunctionCall(*new Token(*current));
					directFunctionCall->setArraySize(2);
					directFunctionCall->setAt(0, SET_CONST_TO_RT);
					directFunctionCall->setAt(1, to_string(getFromArrayLength()).c_str());
					listActionNodes.insertBefore(&actionBefore, directFunctionCall);

					tempPreviousLocalVariable = getPreviousLocalVariableName(sBuffer);

					directFunctionCall = new DirectFunctionCall(*new Token(*current));
					directFunctionCall->setArraySize(2);
					directFunctionCall->setAt(0, SET_GET_FROM_RT);
					directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
					listActionNodes.insertBefore(&actionBefore, directFunctionCall);

					tempCurrentLocalVariable = getCurrentLocalVariableName();
				}

				compiledBodyPart->Compile(cTokenList, *current, *seperator, listActionNodes, *listActionNodes.getLast());

				if (!fromArray) { tempPreviousLocalVariable = getPreviousLocalVariableName(sBuffer); }

				DirectFunctionCall* directFunctionCall = new DirectFunctionCall(*new Token(*current));
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				if (fromArray) { tempCurrentLocalVariable = getCurrentLocalVariableName(); }

				string tempArguments[2];

				/*tempArguments[0] = "$AddLengthToArray";
				tempArguments[1] = currArray;

				FunctionCall* pFunction = new FunctionCall();
				pFunction->setArraySize(2);
				for (int n = 0; n < 2; n++)
				{
					pFunction->setAt(n, tempArguments[n].c_str());
				}
				listActionNodes.insertBefore(&actionBefore, pFunction);*/

				tempArguments[0] = "$AddArrayToDictionary";
				tempArguments[1] = currArray;

				FunctionCall* pFunction = new FunctionCall();
				pFunction->setArraySize(2);
				for (int n = 0; n < 2; n++)
				{
					pFunction->setAt(n, tempArguments[n].c_str());
				}
				listActionNodes.insertBefore(&actionBefore, pFunction);

				string saArguments[4];
				saArguments[0] = "$AddItemToArrayAt";
				if (fromArray)
				{
					string curr = getCurrentLocalVariableName();
					saArguments[1] = currArray;
					saArguments[2] = getPreviousLocalVariableName(sBuffer);
					saArguments[3] = curr;
				}
				else
				{
					saArguments[1] = currArray;
					saArguments[2] = currArrayTempVar;
					saArguments[3] = getCurrentLocalVariableName();
				}

				pFunction = new FunctionCall();
				pFunction->setArraySize(4);
				for (int n = 0; n < 4; n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				listActionNodes.insertBefore(&actionBefore, pFunction);
			}
			else if (current->getEnum() == Token::IDENTIFIER)
			{
				DirectFunctionCall* directFunctionCall = new DirectFunctionCall(*new Token(*current));
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_ID_TO_RT);
				directFunctionCall->setAt(1, current->getText().c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				directFunctionCall = new DirectFunctionCall(*new Token(*current));
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				//currArrayTempVar = getCurrentLocalVariableName();
				currArray = getCurrentLocalVariableName();
			}
			currArrayTempVar = getCurrentLocalVariableName();
			current = current->next;
		}
		else if (expectation.Level >= arrayLevel)
		{
			if (current->getEnum() == Token::ARRAY_CLOSE) {
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, Token::NONE);
				begin = end;
				break;
			}

			Token* seperator = current;
			while (seperator->getEnum() != Token::ARRAY_CLOSE) {
				if (seperator->getEnum() == Token::ARRAY_CLOSE) { break; }
				seperator = seperator->next;
			}

			Compiler* compiledBodyPart;

			bool multiIndex = current->next->getEnum() != Token::ARRAY_CLOSE;

			if (multiIndex) { compiledBodyPart = new CompilePlusMinus(); }
			else { compiledBodyPart = new CompileSingleStatement(); }

			compiledBodyPart->Compile(cTokenList, *current, *seperator, listActionNodes, *listActionNodes.getLast());

			DirectFunctionCall* directFunctionCall = new DirectFunctionCall(*new Token(*current));
			directFunctionCall->setArraySize(2);
			directFunctionCall->setAt(0, SET_GET_FROM_RT);
			directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
			listActionNodes.insertBefore(&actionBefore, directFunctionCall);

			if (!multiIndex) { current = current->next; }
		}
	}

	begin = *current;
}