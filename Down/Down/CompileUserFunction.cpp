#include "stdafx.h"
#include "CompileUserFunction.h"
#include "CompileCondition.h"
#include "CompileFactory.h"
#include "Function.h"
#include "FunctionHandler.h"
#include "TokenExpectation.h"

CompileUserFunction::CompileUserFunction() 
{
	_body			= make_shared<LinkedList>();
	_returnToken	= nullptr;
}

void CompileUserFunction::connectList() 
{
	shared_ptr<Function> funcion = make_shared<Function>(functionName, _params, _body, vector<shared_ptr<Token>>{_paramTokens}, _returnToken, true);
	FunctionHandler::getInstance()->addFunction(funcion);
}

void CompileUserFunction::compile(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
								  shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();
	shared_ptr<Token> bodyEnd = nullptr;

	list<shared_ptr<TokenExpectation>> expected;
	expected.push_back(make_shared<TokenExpectation>(level, IToken::FUNCTION_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::FUNCTION_DECLARE));
	expected.push_back(make_shared<TokenExpectation>(level + 1, IToken::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::FUNCTION_CLOSE));

	for (shared_ptr<TokenExpectation> expectation : expected)
	{
		while (current->getType() == IToken::NEWLINE)
		{
			current = current->getNext();
		}

		if (expectation->getLevel() == level)
		{
			if (current->getType() == IToken::FUNCTION_OPEN)
			{
				bodyEnd = current->getPartner();
			}
			else if (current->getType() == IToken::FUNCTION_DECLARE)
			{
				functionName = current->getText();
			}

			if (current->getType() != expectation->getTokenType()) 
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("", ".md", current->getLevel(), current->getPosition(), ErrorType::error), 
													  expectation->getTokenType(), current->getType());
				begin = end;

				break;
			}
			else
			{
				current = current->getNext();
			}
		}
		else 
		{
			// Check if enum is comingparam else body;
			if (current->getType() == IToken::START_PARAMETERS)
			{
				compileParams(tokenList, current, end);
				compileBody(tokenList, current, bodyEnd, level);
			}
			else
			{
				compileBody(tokenList, current, bodyEnd, level);
			}
		}
	}
	connectList();
	begin = current;
}

void CompileUserFunction::compileParams(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end)
{
	shared_ptr<Token> current = begin;
	
	while (current->getType() != IToken::NEWLINE)
	{
		if (current->getText() == functionName) 
		{
			ErrorHandler::getInstance()->addError(make_shared<Error>(functionName + " Cannot call itself", ".md", current->getLineNumber(), 
												  current->getPosition(), ErrorType::error));
			current = end;

			break;
		}

		if (current->getType() == IToken::IDENTIFIER)
		{
			if (current->getPrevious() != nullptr && current->getPrevious()->getType() == IToken::RETURNVALUE)
			{
				_returnToken = current;
			}
			else 
			{
				switch (current->getSubType()) 
				{
					case IToken::TYPE_NUMBER:
					{
						_params += 'i';

						break;
					}
					case IToken::TYPE_FACT:
					{
						_params += 'b';

						break;
					}
					case IToken::TYPE_TEXT:
					{
						_params += 's';

						break;
					}
					default: 
					{
						_params += 'a';

						break;
					}
				}
				_paramTokens.push_back(current);
			}
		}
		current = current->getNext();
	}
	begin = current;
}

void CompileUserFunction::compileBody(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end, int Level)
{
	shared_ptr<Token> current = begin;

	do 
	{
		if (current->getText() == functionName) 
		{
			ErrorHandler::getInstance()->addError(make_shared<Error>(functionName + " Cannot call itself", ".md", current->getLineNumber(), 
												  current->getPosition(), ErrorType::error));
			current = end;

			break;
		}
		_body->add(current);
		current = current->getNext();
	} 
	while (current->getType() != end->getType());

	begin = current;
}

shared_ptr<Compiler> CompileUserFunction::create()
{
	return make_shared<CompileUserFunction>();
}