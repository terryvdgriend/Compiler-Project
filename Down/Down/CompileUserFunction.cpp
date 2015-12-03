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
	expected.push_back(make_shared<TokenExpectation>(level, Token::FUNCTION_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level, Token::FUNCTION_DECLARE));
	expected.push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, Token::FUNCTION_CLOSE));

	for (shared_ptr<TokenExpectation> expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE) 
		{
			current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
		}

		if (expectation->getLevel() == level)
		{
			if (current->getEnum() == Token::FUNCTION_OPEN) 
			{
				bodyEnd = shared_ptr<Token>(current->getPartner()); // Todo fix tokenizer, will throw error soon
			}
			else if (current->getEnum() == Token::FUNCTION_DECLARE) 
			{
				functionName = current->getText();
			}

			if (current->getEnum() != expectation->getTokenType()) 
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("", ".md", current->getLevel(), current->getPositie(), ErrorType::error), 
													  expectation->getTokenType(), current->getEnum());
				begin = end;

				break;
			}
			else
			{
				current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
		}
		else 
		{
			// Check if enum is comingparam else body;
			if (current->getEnum() == Token::START_PARAMETERS) 
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
	
	while (current->getEnum() != Token::NEWLINE)
	{
		if (current->getText() == functionName) 
		{
			ErrorHandler::getInstance()->addError(make_shared<Error>(functionName + " Cannot call itself", ".md", current->getLineNumber(), 
												  current->getPositie(), ErrorType::error));
			current = end;

			break;
		}

		if (current->getEnum() == Token::IDENTIFIER)
		{
			if (current->previous != nullptr && current->previous->getEnum() == Token::RETURNVALUE) 
			{
				_returnToken = current;
			}
			else 
			{
				switch (current->getSub()) 
				{
					case Token::TYPE_NUMBER: 
					{
						_params += 'i';

						break;
					}
					case Token::TYPE_FACT: 
					{
						_params += 'b';

						break;
					}
					case Token::TYPE_TEXT: 
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
		current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
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
												  current->getPositie(), ErrorType::error));
			current = end;

			break;
		}
		_body->add(new Token(*current));
		current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
	} 
	while (current->getEnum() != end->getEnum());
	begin = current;
}

shared_ptr<Compiler> CompileUserFunction::create()
{
	return make_shared<CompileUserFunction>();
}