#include "stdafx.h"
#include "CompileGetArrayItem.h"
#include "CompilerHeader.h"
#include "DirectFunctionCall.h"
#include "FunctionCall.h"
#include "TokenExpectation.h"

#define SET_ID_TO_RT "IdentifierToReturnValue"
#define SET_CONST_TO_RT "ConstantToReturnValue"
#define SET_GET_FROM_RT "getFromReturnValue"

void CompileGetArrayItem::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
								  shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	vector<string> arrayIndexes;
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	shared_ptr<Token> paraChecker = current;

	while (paraChecker->getType() != IToken::ARRAY_OPEN) {
		paraChecker = paraChecker->getNext();
	}
	shared_ptr<Token> paraCheckerEnd = paraChecker->getPartner();
	stack<IToken> stack;

	while (paraChecker != paraCheckerEnd) {
		if (paraChecker->getType() == IToken::FUNCTION_DECLARE_OPEN)
			stack.push(paraChecker->getType());
		else if (paraChecker->getType() == IToken::FUNCTION_DECLARE_CLOSE)
			stack.pop();
		else if (stack.size() == 0 && paraChecker->getType() == IToken::AND_PARA) {
			isMultiDimensional = true;
			break;
		}
		paraChecker = paraChecker->getNext();
	}

	list<TokenExpectation> expected = list<TokenExpectation>();
	expected.push_back(TokenExpectation(level, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::ARRAY_OPEN));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::ARRAY_CLOSE));

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
            auto error = make_shared<Error>("get an item not completed", ".md", -1, -1, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			begin = end;

			break;
		}
		string sBuffer;

		if (expectation.getLevel() == level)
		{
			if (current->getType() == IToken::IDENTIFIER)
			{
                auto tempToken = make_shared<Token>(current);
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_ID_TO_RT);
				directFunctionCall->setAt(1, current->getText().c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				currentArrayItemTempVar = getCurrentLocalVariableName();
                tempToken= make_shared<Token>(current);
				directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				currentArray = getCurrentLocalVariableName();
				current = current->getNext();
			}
			else if (current->getType() == IToken::FUNCTION_DECLARE_OPEN) {
				CompileGetFunction function;
                auto eNode = current->getPartner();
				function.compile(tokenList, current, eNode, listActionNodes, actionBefore);
				currentArrayItemTempVar = getCurrentLocalVariableName();
                auto tempToken = make_shared<Token>(current);
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				currentArray = getCurrentLocalVariableName();
				current = current->getNext();
			}
			else if(current->getType() != expectation.getTokenType()){
                auto error = make_shared<Error>("", ".md", current->getLevel(), current->getPosition(), ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error,
					expectation.getTokenType(), current->getType());
				begin = end;

				break;
			}
			else {
				current = current->getNext();
			}
			
		}
		else if (expectation.getLevel() > level)
		{
			if (current->getType() == IToken::ARRAY_CLOSE) 
			{
                auto error = make_shared<Error>("No number or identifier found.", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error);
				begin = end;

				break;
			}
			shared_ptr<Token> seperator = current;

			while (seperator->getType() != IToken::ARRAY_OPEN)
			{
				seperator = seperator->getPrevious();
			}
			seperator = seperator->getPartner();

				shared_ptr<Token> arrayClose = current;

				while (arrayClose->getType() != IToken::ARRAY_OPEN)
				{
					arrayClose = arrayClose->getPrevious();
				}
				arrayClose = arrayClose->getPartner();


				vector<shared_ptr<LinkedTokenList>> paramList;
				shared_ptr<LinkedTokenList> param = make_shared<LinkedTokenList>();
				stack.empty();

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
				} while (current != arrayClose);


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


				string currArray = getCurrentLocalVariableName();
				vector<string> saArguments(2+arrayIndexes.size());
				saArguments[0] = "$GetItemFromArray";
				saArguments[1] = currentArray;
				for (size_t i = 0; i < arrayIndexes.size(); i++)
				{
					saArguments[i + 2] = arrayIndexes.at(i);
				}

				shared_ptr<FunctionCall> pFunction = make_shared<FunctionCall>();
				pFunction->setArraySize(saArguments.size());

				for (int n = 0; n < saArguments.size(); n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				listActionNodes->insertBefore(actionBefore, pFunction);
		}
	}
	begin = current;
}

void CompileGetArrayItem::createNewLineToken(shared_ptr<LinkedTokenList>& param, vector<shared_ptr<LinkedTokenList>>& list)
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