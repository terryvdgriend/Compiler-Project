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
			
			if (isMultiDimensional)
			{
				while (current->getType() != IToken::ARRAY_CLOSE)
				{
					auto tempToken = make_shared<Token>(current);
					shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
					directFunctionCall->setArraySize(2);
					directFunctionCall->setAt(0, SET_CONST_TO_RT);
					directFunctionCall->setAt(1, current->getText().c_str());
					listActionNodes->insertBefore(actionBefore, directFunctionCall);

					directFunctionCall = make_shared<DirectFunctionCall>(tempToken);
					directFunctionCall->setArraySize(2);
					directFunctionCall->setAt(0, SET_GET_FROM_RT);
					directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
					listActionNodes->insertBefore(actionBefore, directFunctionCall);

					if (current->getNext()->getType() == IToken::AND_PARA) { current = current->getNext(); }
					current = current->getNext();
				}

				string currArray = getCurrentLocalVariableName();
				string saArguments[4];
				saArguments[0] = "$GetItemFromArray";
				saArguments[1] = currentArray;
				saArguments[2] = getPreviousLocalVariableName(sBuffer);
				saArguments[3] = currArray;

				shared_ptr<FunctionCall> pFunction = make_shared<FunctionCall>();
				pFunction->setArraySize(4);

				for (int n = 0; n < 4; n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				listActionNodes->insertBefore(actionBefore, pFunction);
			}
			else
			{
				compiledBodyPart->compile(tokenList, current, seperator, listActionNodes, actionBefore);
				auto error = make_shared<Token>(current);
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(error);
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				string saArguments[3];
				saArguments[0] = "$GetItemFromArray";
				saArguments[1] = currentArray;
				saArguments[2] = getCurrentLocalVariableName();

				shared_ptr<FunctionCall> pFunction = make_shared<FunctionCall>();
				pFunction->setArraySize(3);

				for (int n = 0; n < 3; n++)
				{
					pFunction->setAt(n, saArguments[n].c_str());
				}
				listActionNodes->insertBefore(actionBefore, pFunction);

				while (current->getType() != IToken::ARRAY_CLOSE)
				{
					current = current->getNext();
				}
			}
		}
	}
	begin = current;
}