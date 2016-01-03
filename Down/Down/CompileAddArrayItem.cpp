#include "stdafx.h"
#include "CompileAddArrayItem.h"
#include "CompileCondition.h"
#include "CompilePlusMinus.h"
#include "CompileSingleStatement.h"
#include "DirectFunctionCall.h"
#include "FunctionCall.h"
#include "TokenExpectation.h"

#define SET_ID_TO_RT "IdentifierToReturnValue"
#define SET_CONST_TO_RT "ConstantToReturnValue"
#define SET_GET_FROM_RT "getFromReturnValue"

void CompileAddArrayItem::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
								  shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	list<TokenExpectation> expected = list<TokenExpectation>();

	if (!fromArray)
	{
		expected.push_back(TokenExpectation(level, IToken::IDENTIFIER));
		expected.push_back(TokenExpectation(level, IToken::ARRAY_OPEN));
		expected.push_back(TokenExpectation(level + 1, IToken::NUMBER));
		expected.push_back(TokenExpectation(level, IToken::ARRAY_CLOSE));
		expected.push_back(TokenExpectation(level, IToken::EQUALS));
		expected.push_back(TokenExpectation(level, IToken::ANY));
	}
	else
	{
		expected.push_back(TokenExpectation(level, IToken::ANY));
	}
	shared_ptr<Token> temp = begin;

	for (TokenExpectation expectation : expected)
	{
		while (current->getType() == IToken::NEWLINE)
		{
			if (current->getNext() != nullptr)
			{
				current = current->getNext();
			}
			else
			{
				break;
			}
		}

		if (current == nullptr) 
		{
            auto error = make_shared<Error>("set an item not completed", ".md", -1, -1, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			begin = end;

			break;
		}
		string sBuffer;

		if (expectation.getLevel() == level)
		{
			if (expectation.getTokenType() != IToken::ANY && current->getType() != expectation.getTokenType()) 
			{
                auto error = make_shared<Error>("", ".md", current->getLevel(), current->getPosition(), ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error,
													  expectation.getTokenType(), current->getType());
				begin = end;

				break;
			}

			if (expectation.getTokenType() == IToken::ANY)
			{
				CompileCondition compiledBodyPart;
				shared_ptr<Token> seperator = current;

				do 
				{
					seperator = seperator->getNext();
				} 
				while (seperator->getType() != IToken::NEWLINE && seperator->getType() != IToken::ARRAY_CLOSE);

				if (fromArray)
				{
					auto tempToken = make_shared<Token>(current);
					if (isMultiDimensional)
					{
						shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
						directFunctionCall->setArraySize(2);
						directFunctionCall->setAt(0, SET_CONST_TO_RT);
						directFunctionCall->setAt(1, to_string(itemPositionInMultiArray[0]).c_str());
						listActionNodes->insertBefore(actionBefore, directFunctionCall);

						directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
						directFunctionCall->setArraySize(2);
						directFunctionCall->setAt(0, SET_GET_FROM_RT);
						directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
						listActionNodes->insertBefore(actionBefore, directFunctionCall);

						currentArrayTempVar = getCurrentLocalVariableName();

						directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
						directFunctionCall->setArraySize(2);
						directFunctionCall->setAt(0, SET_CONST_TO_RT);
						directFunctionCall->setAt(1, to_string(itemPositionInMultiArray[1]).c_str());
						listActionNodes->insertBefore(actionBefore, directFunctionCall);

						directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
						directFunctionCall->setArraySize(2);
						directFunctionCall->setAt(0, SET_GET_FROM_RT);
						directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
						listActionNodes->insertBefore(actionBefore, directFunctionCall);
					}
					else
					{
						shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
						directFunctionCall->setArraySize(2);
						directFunctionCall->setAt(0, SET_CONST_TO_RT);
						directFunctionCall->setAt(1, to_string(getFromArrayLength()).c_str());
						listActionNodes->insertBefore(actionBefore, directFunctionCall);
						tempToken = make_shared<Token>(current);
						directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
						directFunctionCall->setArraySize(2);
						directFunctionCall->setAt(0, SET_GET_FROM_RT);
						directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
						listActionNodes->insertBefore(actionBefore, directFunctionCall);

						currentArrayTempVar = getCurrentLocalVariableName();
					}
				}
				auto eBefore = listActionNodes->getLast();
				auto tempToken = make_shared<Token>(current);

				compiledBodyPart.compile(tokenList, current, seperator, listActionNodes, eBefore);
                
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				string tempArguments[2];

				string current = getCurrentLocalVariableName();
				string saArguments[5];
				shared_ptr<FunctionCall> pFunction = make_shared<FunctionCall>();
				if (isMultiDimensional)
				{
					saArguments[0] = "$AddItemToArrayAt";
					saArguments[1] = currentArray;
					saArguments[2] = currentArrayTempVar;
					saArguments[3] = getPreviousLocalVariableName(sBuffer);
					saArguments[4] = current;

					pFunction->setArraySize(5);

					for (int n = 0; n < 5; n++)
					{
						pFunction->setAt(n, saArguments[n].c_str());
					}
				}
				else
				{
					saArguments[0] = "$AddItemToArrayAt";
					saArguments[1] = currentArray;
					saArguments[2] = currentArrayTempVar;
					saArguments[3] = current;

					pFunction->setArraySize(4);

					for (int n = 0; n < 4; n++)
					{
						pFunction->setAt(n, saArguments[n].c_str());
					}
				}

				listActionNodes->insertBefore(actionBefore, pFunction);
			}
			else if (current->getType() == IToken::IDENTIFIER)
			{
                auto tempToken = make_shared<Token>(current);
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_ID_TO_RT);
				directFunctionCall->setAt(1, current->getText().c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);
                tempToken= make_shared<Token>(current);
				directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				//currentArray = getCurrentArray();
			}

			if (current->getType() != IToken::NEWLINE)
			{
				current = current->getNext();
			}
		}
		else if (expectation.getLevel() >= level)
		{
			if (current->getType() == IToken::ARRAY_CLOSE) 
			{
                auto error = make_shared<Error>("", ".md", current->getLevel(), current->getPosition(), ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error,
													  expectation.getTokenType(), IToken::NONE);
				begin = end;

				break;
			}
			shared_ptr<Token> seperator = current;

			while (seperator->getType() != IToken::ARRAY_OPEN)
			{
				seperator = seperator->getPrevious();
			}
			seperator = seperator->getPartner();
			shared_ptr<Compiler> compiledBodyPart;
			bool multiIndex = false;

			if (current->getNext()->getType() != IToken::ARRAY_CLOSE)
			{
				multiIndex = true;
			}

			if (multiIndex) 
			{ 
				compiledBodyPart = make_shared<CompilePlusMinus>(); 
			}
			else 
			{ 
				compiledBodyPart = make_shared<CompileSingleStatement>();
			}
			auto tempToken = make_shared<Token>(current);
			auto eBefore = listActionNodes->getLast();
            
			compiledBodyPart->compile(tokenList, current, seperator, listActionNodes, eBefore);
            
			shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
			directFunctionCall->setArraySize(2);
			directFunctionCall->setAt(0, SET_GET_FROM_RT);
			directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
			listActionNodes->insertBefore(actionBefore, directFunctionCall);
			currentArrayTempVar = getCurrentLocalVariableName();

			if (!multiIndex) 
			{ 
				current = current->getNext(); 
			}
		}
	}

	if (current != nullptr)
	{
		begin = current;
	}
}

string CompileAddArrayItem::getCurrentArray()
{
	return currentArray;
}

void CompileAddArrayItem::setCurrentArray(string newCurrentArray)
{
	currentArray = newCurrentArray;
}

bool CompileAddArrayItem::isFromArray()
{
	return fromArray;
}

void CompileAddArrayItem::setFromArray(bool newFromArray)
{
	fromArray = newFromArray;
}

int CompileAddArrayItem::getFromArrayLength()
{
	return fromArrayLength;
}

void CompileAddArrayItem::setFromArrayLength(int newFromArrayLength)
{
	fromArrayLength = newFromArrayLength;
}

int* CompileAddArrayItem::getFromMultiArrayLength()
{
	return fromMultiArrayLength;
}

void CompileAddArrayItem::setFromMultiArrayLength(int firstFromMultiArrayLength, int secondFromMultiArrayLength)
{
	fromMultiArrayLength[0] = firstFromMultiArrayLength;
	fromMultiArrayLength[1] = secondFromMultiArrayLength;
}

void CompileAddArrayItem::setItemPositionInMultiArray(int firstItemPositionInMultiArray, int secondItemPositionInMultiArray)
{
	itemPositionInMultiArray[0] = firstItemPositionInMultiArray;
	itemPositionInMultiArray[1] = secondItemPositionInMultiArray;
}