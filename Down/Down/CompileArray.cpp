#include "stdafx.h"

#include "CompileArray.h"

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

CompileArray::CompileArray()
{
}

CompileArray::~CompileArray()
{
}

void CompileArray::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	Token* current = &begin;
	int arrayLevel = begin.getLevel();
	
	list<TokenExpectation> expected = list<TokenExpectation>();
	expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_OPEN));
	expected.push_back(TokenExpectation(arrayLevel + 1, Token::NUMBER));
	expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_CLOSE));
	expected.push_back(TokenExpectation(arrayLevel, Token::IDENTIFIER));
	expected.push_back(TokenExpectation(arrayLevel, Token::EQUALS));
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
			ErrorHandler::getInstance()->addError(Error{ "making array not completed", ".md",-1, -1, Error::error });
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
				CompileSingleStatement* compiledBodyPart = new CompileSingleStatement();
				compiledBodyPart->Compile(cTokenList, *current, *current->next, listActionNodes, *listActionNodes.getLast());

				DirectFunctionCall* directFunctionCall = new DirectFunctionCall;
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				currArrayTempVar = getCurrentLocalVariableName();
				prevArrayTempVar = getPreviousLocalVariableName(sBuffer);
				string saArguments[3];

				saArguments[0] = "$AddLengthToArray";
				saArguments[1] = currArrayTempVar;
				saArguments[2] = prevArrayTempVar;

				FunctionCall* pFunction = new FunctionCall();
				pFunction->setArraySize(3);
				for (int n = 0; n < 3; n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				listActionNodes.insertBefore(&actionBefore, pFunction);

				saArguments[0] = "$AddArrayToDictionary";
				saArguments[1] = currArrayTempVar;
				saArguments[2] = prevArrayTempVar;

				pFunction = new FunctionCall();
				pFunction->setArraySize(2);
				for (int n = 0; n < 2; n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				listActionNodes.insertBefore(&actionBefore, pFunction);

				delete compiledBodyPart;
			}

			current = current->next;
		}
		else if (expectation.Level >= arrayLevel)
		{
			if (expectation.TokenType == Token::ANY)
			{
				Token* prev = current->previous;
				while (prev->getEnum() != Token::ARRAY_OPEN)
				{
					prev = prev->previous;
				}
				prev = prev->getPartner();

				while (current->getLevel() > arrayLevel)
				{
					/*CompileSingleStatement* compiledBodyPart = new CompileSingleStatement();*/
					CompileCondition* compiledBodyPart = new CompileCondition();

					ActionNode* lastActionNode = listActionNodes.getLast()->getPrevious();

					Token* seperator = current;
					while (seperator->getEnum() != Token::AND_PARA || seperator->getEnum() != Token::ARRAY_CLOSE) {
						if (seperator->getEnum() == Token::AND_PARA || seperator->getEnum() == Token::ARRAY_CLOSE) { break; }
						seperator = seperator->next;
					}

					compiledBodyPart->Compile(cTokenList, *current, *seperator, listActionNodes, *listActionNodes.getLast());

					if (lastActionNode != listActionNodes.getLast()->getPrevious())
					{
						DirectFunctionCall* directFunctionCall = new DirectFunctionCall;
						directFunctionCall->setArraySize(2);
						directFunctionCall->setAt(0, SET_GET_FROM_RT);
						directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
						listActionNodes.insertBefore(&actionBefore, directFunctionCall);

						string saArguments[3];

						saArguments[0] = "$AddItemToArray";
						saArguments[1] = currArrayTempVar;
						saArguments[2] = getCurrentLocalVariableName();

						FunctionCall* pFunction = new FunctionCall();
						pFunction->setArraySize(3);
						for (int n = 0; n < 3; n++)
						{
							pFunction->setAt(n, saArguments[n].c_str());
						}
						listActionNodes.insertBefore(&actionBefore, pFunction);
					}

					current = current->next;
					
					delete compiledBodyPart;
				}

				currArrayTempVar = getCurrentLocalVariableName();
			}
			else
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
	}

	begin = *current;
}