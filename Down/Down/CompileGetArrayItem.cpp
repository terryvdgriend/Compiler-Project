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
			ErrorHandler::getInstance()->addError(make_shared<Error>("get an item not completed", ".md", -1, -1, ErrorType::ERROR));
			begin = end;

			break;
		}
		string sBuffer;

		if (expectation.getLevel() == level)
		{
			if (current->getType() == IToken::IDENTIFIER)
			{
				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(make_shared<Token>(current));
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_ID_TO_RT);
				directFunctionCall->setAt(1, current->getText().c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				currentArrayItemTempVar = getCurrentLocalVariableName();

				directFunctionCall = make_shared<DirectFunctionCall>(make_shared<Token>(current));
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				currentArray = getCurrentLocalVariableName();
				current = current->getNext();
			}
			else if (current->getType() == IToken::FUNCTION_DECLARE_OPEN) {
				CompileGetFunction function;
				function.compile(tokenList, current, current->getPartner(), listActionNodes, actionBefore);
				currentArrayItemTempVar = getCurrentLocalVariableName();

				shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(make_shared<Token>(current));
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				listActionNodes->insertBefore(actionBefore, directFunctionCall);

				currentArray = getCurrentLocalVariableName();
			}
			else if(current->getType() != expectation.getTokenType()){
				ErrorHandler::getInstance()->addError(make_shared<Error>("", ".md", current->getLevel(), current->getPosition(), ErrorType::ERROR),
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
				ErrorHandler::getInstance()->addError(make_shared<Error>("No number or identifier found.", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR));
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
			compiledBodyPart->compile(tokenList, current, seperator, listActionNodes, actionBefore);

			shared_ptr<DirectFunctionCall> directFunctionCall = make_shared<DirectFunctionCall>(make_shared<Token>(current));
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
	begin = current;
}