#include "stdafx.h"
#include "CompileDoWhile.h"
#include "CompileCondition.h"
#include "CompileFactory.h"
#include "ConditionalJumpNode.h"
#include "DoNothingNode.h"
#include "TokenExpectation.h"

CompileDoWhile::CompileDoWhile()
{
	_compiledStatement	= make_shared<LinkedActionList>();
	_condition			= make_shared<LinkedActionList>();
	_body				= make_shared<LinkedActionList>();
	_compiledStatement->add(make_shared<DoNothingNode>());
}

void CompileDoWhile::compile(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
							 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	list<shared_ptr<TokenExpectation>> expected;
	expected.push_back(make_shared<TokenExpectation>(level, Token::DO));
	expected.push_back(make_shared<TokenExpectation>(level, Token::BODY_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, Token::BODY_CLOSED));
	expected.push_back(make_shared<TokenExpectation>(level, Token::WHILE));
	expected.push_back(make_shared<TokenExpectation>(level, Token::CONDITION_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, Token::CONDITION_CLOSE));

	for (shared_ptr<TokenExpectation> expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE)
		{
			current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
		}

		if (expectation->getLevel() == level)
		{
			if (current == nullptr)
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("do while statement not completed", ".md", -1, -1, ErrorType::error));
				begin = end;

				break;
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
		else if (expectation->getLevel() >= level)
		{
			if (_body->getCount() == 0)
			{
				shared_ptr<Token> previous = shared_ptr<Token>(current->previous); // Todo fix tokenizer, will throw error soon
				_body->add(make_shared<DoNothingNode>());

				while (previous->getEnum() != Token::BODY_OPEN)
				{
					previous = shared_ptr<Token>(previous->previous); // Todo fix tokenizer, will throw error soon
				}
				previous = shared_ptr<Token>(previous->getPartner()); // Todo fix tokenizer, will throw error soon

				while (current->getLevel() > level)
				{
					shared_ptr<Compiler> compiledBodyPart = factory->createCompileStatement(current);

					if (compiledBodyPart != nullptr)
					{
						compiledBodyPart->compile(tokenList, current, previous, _body, _body->getLast());
					}
					else
					{
						current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
					}
				}
			}
			else
			{
				shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
				condition->compile(tokenList, current, shared_ptr<Token>(current->previous->getPartner()), _condition, _condition->getLast()); // Todo fix tokenizer, will throw error soon
			}
		}
	}
	connectLists();
	listActionNodes->insertBefore(actionBefore, _compiledStatement);
	begin = current;
}

shared_ptr<Compiler> CompileDoWhile::create()
{
	return make_shared<CompileDoWhile>();
}

void CompileDoWhile::connectLists()
{
	shared_ptr<ConditionalJumpNode> conditionalJumpNode = make_shared<ConditionalJumpNode>();
	_compiledStatement->add(_body);
	_compiledStatement->add(_condition);
	_compiledStatement->add(conditionalJumpNode);
	_compiledStatement->add(make_shared<DoNothingNode>());
	conditionalJumpNode->setOnTrue(_body->getFirst());
	conditionalJumpNode->setOnFalse(_compiledStatement->getLast());
}