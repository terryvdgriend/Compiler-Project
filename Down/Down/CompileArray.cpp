#include "stdafx.h"

#include "CompileArray.h"

#include "CompilePlusMinus.h"
#include "CompileSingleStatement.h"
#include "TokenExpectation.h"

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
	bool compiledArraySize = false;
	
	list<TokenExpectation> expected = list<TokenExpectation>();
	expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_OPEN));
	expected.push_back(TokenExpectation(arrayLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_CLOSE));
	expected.push_back(TokenExpectation(arrayLevel, Token::IDENTIFIER));

	bool hasEquals = false;
	Token* seeker = current;
	while (seeker->getEnum() != Token::NEWLINE) {
		if (seeker->getEnum() == Token::EQUALS) {
			hasEquals = true;
			break;
		}
		seeker = seeker->next;
	}

	if (hasEquals)
	{
		expected.push_back(TokenExpectation(arrayLevel, Token::EQUALS));
		expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_OPEN));
		expected.push_back(TokenExpectation(arrayLevel + 1, Token::ANY));
		expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_CLOSE));
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
			ErrorHandler::getInstance()->addError(Error{ "making array not completed", ".md", -1, -1, Error::error });
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

				DirectFunctionCall* directFunctionCall = new DirectFunctionCall(*new Token(*current));
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				currArrayTempVar = getCurrentLocalVariableName();
				string saArguments[3];

				saArguments[0] = "$AddLengthToArray";
				saArguments[1] = currArrayTempVar;
				saArguments[2] = getPreviousLocalVariableName(sBuffer);

				FunctionCall* pFunction = new FunctionCall();
				pFunction->setArraySize(3);
				for (int n = 0; n < 3; n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				listActionNodes.insertBefore(&actionBefore, pFunction);

				saArguments[0] = "$AddArrayToDictionary";
				saArguments[1] = currArrayTempVar;

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
			if (current->getEnum() == Token::ARRAY_CLOSE) {
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, Token::NONE);
				begin = end;
				break;
			}
			if (compiledArraySize)
			{
				Token* arrClose = current;
				while (arrClose->getEnum() != Token::ARRAY_OPEN)
				{
					arrClose = arrClose->previous;
				}
				arrClose = current->getPartner();
				std::vector<LinkedList*> paramList;
				LinkedList* param = new LinkedList();
				std::stack<Token::iToken> stack;

				do {
					if (current->getEnum() == Token::ARRAY_OPEN)
						stack.push(current->getEnum());
					else if (current->getEnum() == Token::ARRAY_CLOSE && stack.size() > 0)
						stack.pop();
					if (stack.size() >= 0) {
						if (stack.size() == 0 && current->getEnum() == Token::AND_PARA) {
							if (param->last != nullptr) {
								CreateNewLineToken(*param, paramList);
							}
							else {
								ErrorHandler::getInstance()->addError(Error{"no assignment is array", ".md", current->getLineNumber(),current->getPositie(), Error::error });
							}
							param = new LinkedList();
						}
						else {
							param->add(new Token(*current));
						}
					}
					current = current->next;
					if (stack.size() == 0 && current->getEnum() == Token::ARRAY_CLOSE) {
						if (param->last != nullptr) {
							CreateNewLineToken(*param,paramList);
						}
						else {
							ErrorHandler::getInstance()->addError(Error{ "no assignment is array", ".md", current->getLineNumber(),current->getPositie(), Error::error });
						}
						param = new LinkedList();
						break;
					}
				} while (current != arrClose);

				for (auto p : paramList) {
					CompileAddArrayItem* compiledBodyPart = new CompileAddArrayItem();

					ActionNode* lastActionNode = listActionNodes.getLast()->getPrevious();

					compiledBodyPart->setFromArray(true);
					compiledBodyPart->setFromArrayLength(filledLength++);
					compiledBodyPart->setCurrentArray(currArrayTempVar);

					compiledBodyPart->Compile(cTokenList, *p->first, *p->last, listActionNodes, *listActionNodes.getLast());

					if (current->getEnum() == Token::AND_PARA) { current = current->next; }

					delete compiledBodyPart;
				}
				currArrayTempVar = getCurrentLocalVariableName();
			}
			else
			{
				Token* seperator = current;
				while (seperator->getEnum() != Token::ARRAY_OPEN)
				{
					seperator = seperator->previous;
				}
				seperator = seperator->getPartner();

				Compiler* compiledBodyPart;

				if (current->next->getEnum() != Token::ARRAY_CLOSE) { compiledBodyPart = new CompilePlusMinus(); }
				else { compiledBodyPart = new CompileSingleStatement(); }

				compiledBodyPart->Compile(cTokenList, *current, *seperator, listActionNodes, *listActionNodes.getLast());

				DirectFunctionCall* directFunctionCall = new DirectFunctionCall(*new Token(*current));
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);
				compiledArraySize = true;
				current = seperator;
			}
		}
	}
	 begin = *current; 
}

void CompileArray::CreateNewLineToken(LinkedList & param, std::vector<LinkedList*>& list) {
	param.last->next = nullptr;
	param.first->previous = nullptr;
	Token* connectToken = new Token();
	connectToken->setEnum(Token::NEWLINE);
	connectToken->setLevel(-1);
	connectToken->setPositie(-1);
	connectToken->setPositieInList(-1);
	connectToken->setRegelnummer(-1);
	connectToken->setText("\n");
	param.add(connectToken);
	list.push_back(&param);
}