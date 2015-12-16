#include "stdafx.h"
#include "CompileArray.h"
#include "CompileAddArrayItem.h"
#include "CompilerHeader.h"
#include "CompileSingleStatement.h"
#include "DirectFunctionCall.h"
#include "FunctionCall.h"
#include "TokenExpectation.h"

#define SET_ID_TO_RT "IdentifierToReturnValue"
#define SET_CONST_TO_RT "ConstantToReturnValue"
#define SET_GET_FROM_RT "getFromReturnValue"

void CompileArray::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
						   shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();
	bool compiledArraySize = false;
	
	list<TokenExpectation> expected = list<TokenExpectation>();
	expected.push_back(TokenExpectation(level, IToken::ARRAY_OPEN));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::ARRAY_CLOSE));
	expected.push_back(TokenExpectation(level, IToken::IDENTIFIER));

	bool hasEquals = false;
	bool hasEqualsWithFunc = false;
	shared_ptr<Token> identifier;
	shared_ptr<Token> seeker = current;

	while (seeker->getType() != IToken::NEWLINE)
	{
		if (seeker->getType() == IToken::EQUALS)
		{
			if (seeker->getNext() != nullptr && seeker->getNext()->getType() == IToken::FUNCTION_DECLARE_OPEN)
				hasEqualsWithFunc = true;
			else
				hasEquals = true;

			break;
		}
		seeker = seeker->getNext();
	}

	if (hasEquals)
	{
		expected.push_back(TokenExpectation(level, IToken::EQUALS));
		expected.push_back(TokenExpectation(level, IToken::ARRAY_OPEN));
		expected.push_back(TokenExpectation(level + 1, IToken::ANY));
		expected.push_back(TokenExpectation(level, IToken::ARRAY_CLOSE));
	}
	else if (hasEqualsWithFunc) {
		expected.push_back(TokenExpectation(level, IToken::EQUALS));
		expected.push_back(TokenExpectation(level, IToken::FUNCTION_DECLARE_OPEN));
		expected.push_back(TokenExpectation(level, IToken::FUNCTION_DECLARE_CLOSE));
	}

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
            auto error = make_shared<Error>("making array not completed", ".md", -1, -1, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			begin = end;

			break;
		}
		string sBuffer;

		if (expectation.getLevel() == level)
		{
			if (current->getType() != expectation.getTokenType()) 
			{
                auto error = make_shared<Error>("", ".md", current->getLevel(), current->getPosition(), ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error,
													  expectation.getTokenType(), current->getType());
				begin = end;

				break;
			}
			
			else if (current->getType() == IToken::FUNCTION_DECLARE_OPEN && current->getType() == expectation.getTokenType()) {
				CompileEquals copiler;
                auto eNode = current->getPartner();
				copiler.compile(tokenList, identifier, eNode, listActionNodes, actionBefore);
                auto tempToken = make_shared<Token>(current);
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);
				current = identifier;
			}

			else if (current->getType() == IToken::IDENTIFIER)
			{
				CompileSingleStatement compiledBodyPart;
                auto eNode = current->getNext();
                auto eBefore = listActionNodes->getLast();
                compiledBodyPart.compile(tokenList, current, eNode, listActionNodes, eBefore);
                auto tempToken = make_shared<Token>(current);
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				currentArrayTempVar = getCurrentLocalVariableName();
				string saArguments[3];

				saArguments[0] = "$AddLengthToArray";
				saArguments[1] = currentArrayTempVar;
				saArguments[2] = getPreviousLocalVariableName(sBuffer);

				shared_ptr<FunctionCall> pFunction = make_shared<FunctionCall>();
				pFunction->setArraySize(3);

				for (int n = 0; n < 3; n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				listActionNodes->insertBefore(actionBefore, pFunction);

				saArguments[0] = "$AddArrayToDictionary";
				saArguments[1] = currentArrayTempVar;

				pFunction = make_shared<FunctionCall>();
				pFunction->setArraySize(2);

				for (int n = 0; n < 2; n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				listActionNodes->insertBefore(actionBefore, pFunction);
				if (hasEqualsWithFunc) {
					identifier = current;
				}
				current = current->getNext();
			}
			else {
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

			if (compiledArraySize)
			{
				shared_ptr<Token> arrayClose = current;

				while (arrayClose->getType() != IToken::ARRAY_OPEN)
				{
					arrayClose = arrayClose->getPrevious();
				}
				arrayClose = current->getPartner();
				vector<shared_ptr<LinkedTokenList>> paramList;
				shared_ptr<LinkedTokenList> param = make_shared<LinkedTokenList>();
				stack<IToken> stack;

				do 
				{
					if (current->getType() == IToken::ARRAY_OPEN)
					{
						stack.push(current->getType());
					}
					else if (current->getType() == IToken::ARRAY_CLOSE && stack.size() > 0)
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
                                auto error = make_shared<Error>("no assignment is array", ".md", current->getLineNumber(),
                                                                current->getPosition(), ErrorType::ERROR);
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
                            auto error = make_shared<Error>("no assignment is array", ".md", current->getLineNumber(),
                                                            current->getPosition(), ErrorType::ERROR);
							ErrorHandler::getInstance()->addError(error);
						}
						param = make_shared<LinkedTokenList>();

						break;
					}
				} 
				while (current != arrayClose);

				for (shared_ptr<LinkedTokenList> p : paramList) 
				{
					CompileAddArrayItem compiledBodyPart;
					shared_ptr<ActionNode> lastActionNode = listActionNodes->getLast()->getPrevious();

					compiledBodyPart.setFromArray(true);
					compiledBodyPart.setFromArrayLength(filledLength++);
					compiledBodyPart.setCurrentArray(currentArrayTempVar);
                    
                    auto fNode =  p->getFirst();
                    auto eNode = p->getLast();
                    auto eBefore =listActionNodes->getLast();
					compiledBodyPart.compile(tokenList,fNode, eNode, listActionNodes, eBefore);

					if (current->getType() == IToken::AND_PARA) 
					{ 
						current = current->getNext(); 
					}
				}
				currentArrayTempVar = getCurrentLocalVariableName();
			}
			else
			{
				shared_ptr<Token> seperator = current;

				while (seperator->getType() != IToken::ARRAY_OPEN)
				{
					seperator = seperator->getPrevious();
				}
				seperator = seperator->getPartner();

				shared_ptr<Compiler> compiledBodyPart;

				if (current->getNext()->getType() != IToken::ARRAY_CLOSE) 
				{ 
					compiledBodyPart = make_shared<CompilePlusMinus>(); 
				}
				else 
				{ 
					compiledBodyPart = make_shared<CompileSingleStatement>(); 
				}
                auto eBefore = listActionNodes->getLast();
				compiledBodyPart->compile(tokenList, current, seperator, listActionNodes, eBefore);

                auto tempToken = make_shared<Token>(current);
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);
				compiledArraySize = true;
				current = seperator;
			}
		}
	}
	begin = current; 
}

void CompileArray::createNewLineToken(shared_ptr<LinkedTokenList>& param, vector<shared_ptr<LinkedTokenList>>& list) 
{
	param->getLast()->setNext(nullptr);
	param->getFirst()->setPrevious(nullptr);
	shared_ptr<Token> connectToken = make_shared<Token>();
	connectToken->setType(IToken::NEWLINE);
	connectToken->setLevel(-1);
	connectToken->setPosition(-1);
	connectToken->setPositionInList(-1);
	connectToken->setLineNumber(-1);
	connectToken->setText("\n");
	param->add(connectToken);
	list.push_back(param);
}