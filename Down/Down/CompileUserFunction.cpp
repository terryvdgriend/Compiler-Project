#include "stdafx.h"
#include "CompileUserFunction.h"
#include "CompileCondition.h"
#include "CompileFactory.h"
#include "Function.h"
#include "FunctionHandler.h"
#include "TokenExpectation.h"

CompileUserFunction::CompileUserFunction() 
{
	_body			= make_shared<LinkedTokenList>();
	_returnToken	= nullptr;
}

void CompileUserFunction::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
								  shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();
	shared_ptr<Token> bodyEnd = nullptr;

	list<TokenExpectation> expected;
	expected.push_back(TokenExpectation(level, IToken::FUNCTION_OPEN));
	expected.push_back(TokenExpectation(level, IToken::FUNCTION_DECLARE));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::FUNCTION_CLOSE));

	for (TokenExpectation expectation : expected)
	{
		while (current->getType() == IToken::NEWLINE)
		{
			current = current->getNext();
		}

		if (expectation.getLevel() == level)
		{
			if (current->getType() == IToken::FUNCTION_OPEN)
			{
				bodyEnd = current->getPartner();
			}
			else if (current->getType() == IToken::FUNCTION_DECLARE)
			{
				functionName = current->getText();
			}

			if (current->getType() != expectation.getTokenType()) 
			{
                auto error = make_shared<Error>("", ".md", current->getLevel(), current->getPosition(), ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error,
													  expectation.getTokenType(), current->getType());
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
			// Check if the coming param is an enum, else body;
			if (current->getType() == IToken::START_PARAMETERS)
			{
				compileParams(current, end);
				compileBody(current, bodyEnd);
			}
			else
			{
				compileBody(current, bodyEnd);
			}
		}
	}
	connectList();
	begin = current;
}

void CompileUserFunction::compileParams(shared_ptr<Token>& begin, shared_ptr<Token>& end)
{
	shared_ptr<Token> current = begin;
	
	while (current->getType() != IToken::NEWLINE)
	{
		if (current->getText() == functionName) 
		{
            auto error = make_shared<Error>(functionName + " Cannot call itself", ".md", current->getLineNumber(),
            current->getPosition(), ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			current = end;

			break;
		}

		if (current->getType() == IToken::IDENTIFIER)
		{
			if (current->getPrevious() != nullptr)
			{
				if(current->getPrevious()->getType() == IToken::RETURNVALUE)
					_returnToken = make_shared<Token>(current);
				else if (current->getPrevious()->getType() == IToken::ARRAY_CLOSE && current->getPrevious()->getPartner()->getPrevious() != nullptr && current->getPrevious()->getPartner()->getPrevious()->getType() == IToken::RETURNVALUE)
					_returnToken = make_shared<Token>(current);
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
					_paramTokens.push_back(make_shared<Token>(current));
				}
			}
			
		}
		current = current->getNext();
	}
	begin = current;
}

void CompileUserFunction::compileBody(shared_ptr<Token>& begin, shared_ptr<Token>& end)
{
	shared_ptr<Token> current = begin;

	do 
	{
		if (current->getText() == functionName) 
		{
            auto error = make_shared<Error>(functionName + " Cannot call itself", ".md", current->getLineNumber(),
                                            current->getPosition(), ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
			current = end;

			break;
		}
		_body->add(make_shared<Token>(current));
		current = current->getNext();
	} 
	while (current->getType() != end->getType());

	begin = current;
}

void CompileUserFunction::connectList()
{
	shared_ptr<Function> funcion = make_shared<Function>(functionName, _params, _body, _paramTokens, _returnToken, true);
	FunctionHandler::getInstance()->addFunction(funcion);
}