#include "stdafx.h"
#include "CompileFor.h"
#include "CompileCondition.h"
#include "CompileFactory.h"
#include "ConditionalJumpNode.h"
#include "DoNothingNode.h"
#include "JumpGoToNode.h"
#include "TokenExpectation.h"

CompileFor::CompileFor()
{
	_compiledStatement	= make_shared<LinkedActionList>();
	_declaration		= make_shared<LinkedActionList>();
	_increment			= make_shared<LinkedActionList>();
	_condition			= make_shared<LinkedActionList>();
	_body				= make_shared<LinkedActionList>();
	_compiledStatement->add(make_shared<DoNothingNode>());
}

void CompileFor::compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
	shared_ptr<Token> current = make_shared<Token>(begin);
	int level = begin.getLevel();

	unique_ptr<list<shared_ptr<TokenExpectation>>> expected = make_unique<list<shared_ptr<TokenExpectation>>>();
	expected->push_back(make_shared<TokenExpectation>(level, Token::FOR));
	expected->push_back(make_shared<TokenExpectation>(level, Token::CONDITION_OPEN));
	expected->push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected->push_back(make_shared<TokenExpectation>(level + 1, Token::AND_PARA));
	expected->push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected->push_back(make_shared<TokenExpectation>(level + 1, Token::AND_PARA));
	expected->push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected->push_back(make_shared<TokenExpectation>(level, Token::CONDITION_CLOSE));
	expected->push_back(make_shared<TokenExpectation>(level, Token::BODY_OPEN));
	expected->push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected->push_back(make_shared<TokenExpectation>(level, Token::BODY_CLOSED));

	shared_ptr<Token> conClose = nullptr;

	for (shared_ptr<TokenExpectation> expectation : *expected)
	{
		while (current->getEnum() == Token::NEWLINE)
		{
			current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
		}

		if (expectation->Level == level)
		{
			if (current == nullptr)
			{
				ErrorHandler::getInstance()->addError(Error{ "for statement not completed", ".md", -1, -1, Error::error });
				begin = end;

				break;
			}

			if (current->getEnum() == Token::CONDITION_OPEN)
			{
				conClose = shared_ptr<Token>(current->getPartner()); // Todo fix tokenizer, will throw error soon
			}

			if (current->getEnum() != expectation->TokenType)
			{
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation->TokenType, current->getEnum());
				begin = end;

				break;
			}
			else
			{
				current = shared_ptr<Token>(current->next);
			}
		}
		else if (expectation->Level >= level)
		{
			if (current->getEnum() == expectation->TokenType && current->getEnum() == Token::AND_PARA) 
			{
				current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon

				continue;
			}

			if (_declaration->getCount() == 0)
			{
				shared_ptr<Token> next = shared_ptr<Token>(current->previous); // Todo fix tokenizer, will throw error soon

				while (next->getEnum() != Token::AND_PARA)
				{
					next = shared_ptr<Token>(next->next); // Todo fix tokenizer, will throw error soon
				}
				// Compile the first part of the for-loop
				shared_ptr<Compiler> compiledBodyPart = factory->createCompileStatement(*current);

				if (compiledBodyPart != nullptr)
				{
					compiledBodyPart->compile(cTokenList, *current, *next, *_declaration, *_declaration->getLast());
				}
				else
				{
					current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
				}
			}
			else if (_condition->getCount() == 0)
			{
				shared_ptr<Token> next = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon

				while (next->getEnum() != Token::AND_PARA) 
				{
					next = shared_ptr<Token>(next->next); // Todo fix tokenizer, will throw error soon
				}
				shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
				_condition->add(make_shared<DoNothingNode>());
				condition->compile(cTokenList, *current, *next, *_condition, *_condition->getLast());
			}
			else if (_increment->getCount() == 0)
			{
				// Compile the last part of the for-loop
				shared_ptr<Compiler> compiledBodyPart = factory->createCompileStatement(*current);

				if (compiledBodyPart != nullptr)
				{
					compiledBodyPart->compile(cTokenList, *current, *conClose, *_increment, *_increment->getLast());
				}
				else
				{
					current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
				}
			}
			else
			{
				shared_ptr<Token> previous = shared_ptr<Token>(current->previous); // Todo fix tokenizer, will throw error soon

				while (previous->getEnum() != Token::BODY_OPEN) 
				{
					previous = shared_ptr<Token>(previous->previous);
				}
				previous = shared_ptr<Token>(previous->getPartner());

				while (current->getLevel() > level)
				{
					shared_ptr<Compiler> compiledBodyPart = factory->createCompileStatement(*current);

					if (compiledBodyPart != nullptr) 
					{
						compiledBodyPart->compile(cTokenList, *current, *previous, *_body, *_body->getLast());
					}
					else
					{
						current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
					}
				}
			}
		}
	}
	connectLists();
	listActionNodes.insertBefore(shared_ptr<ActionNode>(&actionBefore), _compiledStatement);
	begin = *current;
}

shared_ptr<Compiler> CompileFor::create()
{
	return make_shared<CompileFor>();
}

void CompileFor::connectLists()
{
	shared_ptr<ConditionalJumpNode> conditionalJumpNode = make_shared<ConditionalJumpNode>();
	shared_ptr<JumpGoToNode> jumpBackNode = make_shared<JumpGoToNode>();
	_compiledStatement->add(_declaration);
	_compiledStatement->add(_condition);
	_compiledStatement->add(conditionalJumpNode);
	_compiledStatement->add(_body);
	_compiledStatement->add(_increment);
	_compiledStatement->add(jumpBackNode);
	_compiledStatement->add(make_shared<DoNothingNode>());
	jumpBackNode->setJumpToNode(_condition->getFirst());
	conditionalJumpNode->setOnTrue(_body->getFirst());
	conditionalJumpNode->setOnFalse(_compiledStatement->getLast());
}