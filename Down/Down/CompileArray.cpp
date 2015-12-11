#include "stdafx.h"
#include "CompileArray.h"
#include "CompileAddArrayItem.h"
#include "CompilePlusMinus.h"
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
	shared_ptr<Token> seeker = current;

	while (seeker->getType() != IToken::NEWLINE)
	{
		if (seeker->getType() == IToken::EQUALS)
		{
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
			ErrorHandler::getInstance()->addError(make_shared<Error>("making array not completed", ".md", -1, -1, ErrorType::ERROR));
			begin = end;

			break;
		}
		string sBuffer;

		if (expectation.getLevel() == level)
		{
			if (current->getType() != expectation.getTokenType()) 
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("", ".md", current->getLevel(), current->getPosition(), ErrorType::ERROR), 
													  expectation.getTokenType(), current->getType());
				begin = end;

				break;
			}

			if (current->getType() == IToken::IDENTIFIER)
			{
				CompileSingleStatement compiledBodyPart;
				compiledBodyPart.compile(tokenList, current, current->getNext(), listActionNodes, listActionNodes->getLast());

				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(make_shared<Token>(current));
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
			}
			current = current->getNext();
		}
		else if (expectation.getLevel() >= level)
		{
			if (current->getType() == IToken::ARRAY_CLOSE) 
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("", ".md", current->getLevel(), current->getPosition(), ErrorType::ERROR), 
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
								ErrorHandler::getInstance()->addError(make_shared<Error>("no assignment is array", ".md", current->getLineNumber(), 
																	  current->getPosition(), ErrorType::ERROR));
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
							ErrorHandler::getInstance()->addError(make_shared<Error>("no assignment is array", ".md", current->getLineNumber(), 
																  current->getPosition(), ErrorType::ERROR));
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

					compiledBodyPart.compile(tokenList, p->getFirst(), p->getLast(), listActionNodes, listActionNodes->getLast());

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
				compiledBodyPart->compile(tokenList, current, seperator, listActionNodes, listActionNodes->getLast());

				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(make_shared<Token>(current));
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