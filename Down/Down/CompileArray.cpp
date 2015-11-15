#include "stdafx.h"
#include "CompileArray.h"

#include "CompileEquals.h"

#include "ConditionalJumpNode.h"
#include "JumpGotoNode.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"
#include "TokenExpectation.h"
#include "CompileSingleStatement.h"

// Normal definitions
#define SET_ID_TO_RT "IdentifierToReturnValue"
#define SET_CONST_TO_RT "ConstantToReturnValue"
#define SET_GET_FROM_RT "getFromReturnValue"

// Array definitions
#define SET_ARRAYID_TO_RT "ArrayIdentifierToReturnValue"
#define SET_ARRAYLENGTH_TO_RT "ArrayLengthToReturnValue"
#define SET_GET_ARRAYLENGTH_FROM_TV "getArrayLengthFromTempValue"
#define SET_ADD_CONST_FROM_RT_TO_ARRAY "addConstantToArray"

CompileArray::CompileArray()
	: CompileOperator(new CompileEquals())
{
	TokenMap &tokenMap = getTokenMap();
	tokenMap[Token::ARRAY_OPEN] = "${";

	_compiledArray = new LinkedActionList();
	_arrayBody = new LinkedActionList();
}

CompileArray::~CompileArray()
{
	delete _compiledArray, _arrayBody;
}

void CompileArray::connectList()
{
	_compiledArray->add(new DoNothingNode());
	_compiledArray->add(_arrayBody);
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
			ErrorHandler::getInstance()->addError(Error{ "array making not completed", ".md",-1, -1, Error::error });
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
				//compiledBodyPart->Compile(cTokenList, *current, *current->next, *_arrayBody, *_arrayBody->getLast());
				compiledBodyPart->Compile(cTokenList, *current, *current->next, listActionNodes, *listActionNodes.getLast());

				DirectFunctionCall* directFunctionCall = new DirectFunctionCall;
				directFunctionCall->setArraySize(2);
				directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				//_arrayBody->add(listActionNodes.insertBefore(&actionBefore, directFunctionCall));
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);
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
					CompileSingleStatement* compiledBodyPart = new CompileSingleStatement();
					//compiledBodyPart->Compile(cTokenList, *current, *prev, *_arrayBody, *_arrayBody->getLast());

					ActionNode* lastActionNode = listActionNodes.getLast()->getPrevious();

					compiledBodyPart->Compile(cTokenList, *current, *prev, listActionNodes, *listActionNodes.getLast());

					if (lastActionNode != listActionNodes.getLast()->getPrevious())
					{
						string nlvn = getNextLocalVariableName(sBuffer);

						DirectFunctionCall* directFunctionCall = new DirectFunctionCall;
						directFunctionCall->setArraySize(2);
						directFunctionCall->setAt(0, SET_GET_FROM_RT);
						//directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
						directFunctionCall->setAt(1, nlvn.c_str());
						//_arrayBody->add(listActionNodes.insertBefore(&actionBefore, directFunctionCall));
						listActionNodes.insertBefore(&actionBefore, directFunctionCall);

						directFunctionCall = new DirectFunctionCall;
						directFunctionCall->setArraySize(2);
						directFunctionCall->setAt(0, SET_ADD_CONST_FROM_RT_TO_ARRAY);
						//directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
						directFunctionCall->setAt(1, nlvn.c_str());
						//_arrayBody->add(listActionNodes.insertBefore(&actionBefore, directFunctionCall));
						listActionNodes.insertBefore(&actionBefore, directFunctionCall);
					}

					current = current->next;
					
					delete compiledBodyPart;
				}
			}
			else
			{
				Token* prev = current->previous;
				while (prev->getEnum() != Token::ARRAY_OPEN)
				{
					prev = prev->previous;
				}
				prev = prev->getPartner();

				CompileOperator* oper;
				//CompileSingleStatement* compiledBodyPart = new CompileSingleStatement();
				//compiledBodyPart->Compile(cTokenList, *current, *prev, *_arrayBody, *_arrayBody->getLast());
				//compiledBodyPart->Compile(cTokenList, *current, *prev, listActionNodes, *listActionNodes.getLast());

				DirectFunctionCall* directFunctionCall = new DirectFunctionCall;
				directFunctionCall->setArraySize(2);
				//directFunctionCall->setAt(0, SET_CONST_TO_RT);
				directFunctionCall->setAt(0, SET_ARRAYLENGTH_TO_RT); // Use to set the length of the array
				directFunctionCall->setAt(1, current->getText().c_str());
				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				directFunctionCall = new DirectFunctionCall;
				directFunctionCall->setArraySize(2);
				//directFunctionCall->setAt(0, SET_GET_FROM_RT);
				directFunctionCall->setAt(0, SET_GET_ARRAYLENGTH_FROM_TV); // Use to get the length of the array
				directFunctionCall->setAt(1, getNextLocalVariableName(sBuffer).c_str());
				/*_arrayBody->add(listActionNodes.insertBefore(&actionBefore, directFunctionCall));*/

				listActionNodes.insertBefore(&actionBefore, directFunctionCall);

				//_arrayBody->add(new DoNothingNode());

				current = current->next;
			}
		}
	}

	//connectList();
	//listActionNodes.add(_compiledArray);
	begin = *current;
}