#include "stdafx.h"

#include "CompileGetArrayItem.h"

#include "CompileEquals.h"
#include "CompilePlusMinus.h"

#include "ConditionalJumpNode.h"
#include "JumpGotoNode.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"
#include "TokenExpectation.h"
#include "CompileSingleStatement.h"

#define SET_ID_TO_RT "IdentifierToReturnValue"
#define SET_CONST_TO_RT "ConstantToReturnValue"
#define SET_GET_FROM_RT "getFromReturnValue"

CompileGetArrayItem::CompileGetArrayItem()
{
}

CompileGetArrayItem::~CompileGetArrayItem()
{
}

void CompileGetArrayItem::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	Token* current = &begin;
	int arrayLevel = begin.getLevel();

	list<TokenExpectation> expected = list<TokenExpectation>();
	expected.push_back(TokenExpectation(arrayLevel, Token::IDENTIFIER));
	expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_OPEN));
	expected.push_back(TokenExpectation(arrayLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_CLOSE));

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
			ErrorHandler::getInstance()->addError(Error{ "get an item not completed", ".md",-1, -1, Error::error });
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

				currArrayItemTempVar = getCurrentLocalVariableName();

				directFunctionCall = new DirectFunctionCall;
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				currArray = getCurrentLocalVariableName();
			}

			current = current->next;
		}
		else if (expectation.Level > arrayLevel)
		{
			if (current->getEnum() == Token::ARRAY_CLOSE) {
				ErrorHandler::getInstance()->addError(Error{ "No number or identifier found.", ".md", current->getLineNumber(), current->getPositie(), Error::error });
				begin = end;
				break;
			}

			Token* prev = current->previous;
			while (prev->getEnum() != Token::ARRAY_OPEN)
			{
				prev = prev->previous;
			}
			prev = prev->getPartner();

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

			DirectFunctionCall* directFunctionCall = new DirectFunctionCall;
			directFunctionCall->setArraySize(2);
			directFunctionCall->setAt(0, SET_GET_FROM_RT);
			directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
			listActionNodes.insertBefore(&actionBefore, directFunctionCall);

			///*DirectFunctionCall* directFunctionCall = new DirectFunctionCall;
			//directFunctionCall->setArraySize(2);
			//directFunctionCall->setAt(0, SET_CONST_TO_RT);
			//directFunctionCall->setAt(1, current->getText().c_str());
			//listActionNodes.insertBefore(&actionBefore, directFunctionCall);

			//directFunctionCall = new DirectFunctionCall;
			//directFunctionCall->setArraySize(2);
			//directFunctionCall->setAt(0, SET_GET_FROM_RT);
			//directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
			//listActionNodes.insertBefore(&actionBefore, directFunctionCall);*/

			string saArguments[3];
			saArguments[0] = "$GetItemFromArray";
			saArguments[1] = currArray;
			saArguments[2] = getCurrentLocalVariableName();

			FunctionCall* pFunction = new FunctionCall();
			pFunction->setArraySize(3);
			for (int n = 0; n < 3; n++)
			{
				pFunction->setAt(n, saArguments[n].c_str());
			}
			listActionNodes.insertBefore(&actionBefore, pFunction);

			/*string temp = currArrayItemTempVar;
			currArrayItemTempVar = getNextLocalVariableName(sBuffer);*/

			directFunctionCall = new DirectFunctionCall;
			directFunctionCall->setArraySize(2);
			directFunctionCall->setAt(0, SET_GET_FROM_RT);
			directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
			listActionNodes.insertBefore(&actionBefore, directFunctionCall);

			saArguments[0] = "$=";
			saArguments[1] = currArrayItemTempVar;
			saArguments[2] = getCurrentLocalVariableName();

			pFunction = new FunctionCall();
			pFunction->setArraySize(3);
			for (int n = 0; n < 3; n++)
			{
				pFunction->setAt(n, saArguments[n].c_str());
			}
			listActionNodes.insertBefore(&actionBefore, pFunction);

			if (!multiIndex) { current = current->next; }
		}
	}

	begin = *current;
}