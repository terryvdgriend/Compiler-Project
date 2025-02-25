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
	bool pastIndex = false;
	vector<string> arrayIndexes;

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
                auto error = make_shared<Error>("", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error, expectation.getTokenType(), current->getType());
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

						for (auto it : itemPositionInMultiArray) {
							auto constTempToken = make_shared<Token>(current);
							constTempToken->setSubType(IToken::TYPE_NUMBER);
							shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(constTempToken);
							directFunctionCall->setArraySize(2);
							directFunctionCall->setAt(0, SET_CONST_TO_RT);
							directFunctionCall->setAt(1, to_string(it).c_str());
							listActionNodes->insertBefore(actionBefore, directFunctionCall);

							directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
							directFunctionCall->setArraySize(2);
							directFunctionCall->setAt(0, SET_GET_FROM_RT);
							directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
							listActionNodes->insertBefore(actionBefore, directFunctionCall);

							arrayIndexes.push_back(getCurrentLocalVariableName());
						}
				}
				auto eBefore = actionBefore;
				auto tempToken = make_shared<Token>(current);

				compiledBodyPart.compile(tokenList, current, seperator, listActionNodes, eBefore);
                
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);
				
				string tempArguments[2];

				string current = getCurrentLocalVariableName();
				int Size = 0;
				Size = 3+(arrayIndexes.size());

				vector<string> saArguments(Size);
				shared_ptr<FunctionCall> pFunction = make_shared<FunctionCall>(tempToken);
				//HIER ARRAY INDEXES ERIN GOOIEN!!!!
				saArguments[0] = "$AddItemToArrayAt";
				saArguments[1] = currentArray;
				int count = 2;
				for(auto it : arrayIndexes)
				{
					saArguments[count] = it;
					count++;
				}
				saArguments[count] = current;

				pFunction->setArraySize(saArguments.size());

				for (size_t n = 0; n < saArguments.size(); n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				
				

				listActionNodes->insertBefore(actionBefore, pFunction);
			}
			else if (current->getType() == IToken::IDENTIFIER)
			{
				currentArray = getNextLocalVariableName(sBuffer).c_str();
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
				directFunctionCall->setAt(1, currentArray.c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);
				
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
                auto error = make_shared<Error>("", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error,
													  expectation.getTokenType(), IToken::NONE);
				begin = end;

				break;
			}

			shared_ptr<Token> arrayClose = current;

			while (arrayClose->getType() != IToken::ARRAY_OPEN)
			{
				arrayClose = arrayClose->getPrevious();
			}
			arrayClose = arrayClose->getPartner();


			vector<shared_ptr<LinkedTokenList>> paramList;
			shared_ptr<LinkedTokenList> param = make_shared<LinkedTokenList>();
			stack<IToken> stack;

			do
			{
				if (current->getType() == IToken::ARRAY_OPEN || current->getType() == IToken::FUNCTION_DECLARE_OPEN)
				{
					stack.push(current->getType());
				}
				else if ((current->getType() == IToken::ARRAY_CLOSE || current->getType() == IToken::FUNCTION_DECLARE_CLOSE) && stack.size() > 0)
				{
					stack.pop();
				}

				if (stack.size() >= 0)
				{
					if (stack.size() == 0 && current->getType() == IToken::AND_PARA)
					{
						if (param->getLast() != nullptr)
						{
							createNewLineToken(param, paramList);
						}
						else
						{
							auto error = make_shared<Error>("no assignment is array", ".md", current->getLineNumber(),current->getPosition(), ErrorType::ERROR);
							ErrorHandler::getInstance()->addError(error);
						}
						param = make_shared<LinkedTokenList>();
					}
					else
					{
						param->add(make_shared<Token>(current));
					}
				}
				current = current->getNext();

				if (stack.size() == 0 && current->getType() == IToken::ARRAY_CLOSE)
				{
					if (param->getLast() != nullptr)
					{
						createNewLineToken(param, paramList);
					}
					else
					{
						auto error = make_shared<Error>("no assignment is array", ".md", current->getLineNumber(),current->getPosition(), ErrorType::ERROR);
						ErrorHandler::getInstance()->addError(error);
					}
					param = make_shared<LinkedTokenList>();

					break;
				}
			} while (current != arrayClose);

			if (paramList.size() > 1) {
				isMultiDimensional = true;
				pastIndex = true;
			}
			shared_ptr<Compiler> compiledBodyPart;
			for (auto params : paramList) {
				 if (params->getSize() >2)
				{ 
					compiledBodyPart = make_shared<CompilePlusMinus>(); 
				}
				else 
				{ 
					compiledBodyPart = make_shared<CompileSingleStatement>();
				}
				auto tempToken = make_shared<Token>(current);
				auto eFirst = params->getFirst();
				auto eLast = params->getLast();
				auto eBefore = actionBefore;
				         
				compiledBodyPart->compile(tokenList, eFirst, eLast, listActionNodes, eBefore);
				         
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);
				arrayIndexes.push_back(getCurrentLocalVariableName());
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

vector<int> CompileAddArrayItem::getFromMultiArrayLength()
{
	return fromMultiArrayLength;
}

void CompileAddArrayItem::setFromMultiArrayLength(vector<int>setIndexFromMulti)
{
	fromMultiArrayLength = setIndexFromMulti;
}

void CompileAddArrayItem::setItemPositionInMultiArray(vector<int> PositionInMultiArray)
{
	itemPositionInMultiArray = PositionInMultiArray;
}

void CompileAddArrayItem::createNewLineToken(shared_ptr<LinkedTokenList>& param, vector<shared_ptr<LinkedTokenList>>& list)
{
	param->getLast()->setNext(nullptr);
	param->getFirst()->setPrevious(nullptr);
	shared_ptr<Token> connectToken = make_shared<Token>();
	connectToken->setType(IToken::NEWLINE);
	connectToken->setLevel(param->getLast()->getLevel());
	connectToken->setPosition(param->getLast()->getPosition());
	connectToken->setPositionInList(param->getLast()->getPosition());
	connectToken->setLineNumber(param->getLast()->getLineNumber());
	connectToken->setText("\n");
	param->add(connectToken);
	list.push_back(param);
}