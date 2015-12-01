#include "stdafx.h"
#include "CompileElseIf.h"
#include "CompileCondition.h"
#include "CompileFactory.h"
#include "ConditionalJumpNode.h"
#include "DoNothingNode.h"
#include "TokenExpectation.h"

CompileElseIf::CompileElseIf()
{
	_compiledStatement	= make_shared<LinkedActionList>();
	_condition			= make_shared<LinkedActionList>();
	_body				= make_shared<LinkedActionList>();
	_compiledStatement->add(shared_ptr<DoNothingNode>());
}

void CompileElseIf::compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	// No implementation - specific implementation below
}

void CompileElseIf::compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore, map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>& _conditionBodyMap)
{
	unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
	shared_ptr<Token> current = make_shared<Token>(begin);
	int level = begin.getLevel();

	unique_ptr<list<shared_ptr<TokenExpectation>>> expected = make_unique<list<shared_ptr<TokenExpectation>>>();
	expected->push_back(make_shared<TokenExpectation>(level, Token::ELIF));
	expected->push_back(make_shared<TokenExpectation>(level, Token::CONDITION_OPEN));
	expected->push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected->push_back(make_shared<TokenExpectation>(level, Token::CONDITION_CLOSE));
	expected->push_back(make_shared<TokenExpectation>(level, Token::BODY_OPEN));
	expected->push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected->push_back(make_shared<TokenExpectation>(level, Token::BODY_CLOSED));

	for (shared_ptr<TokenExpectation> expectation : *expected)
	{
		while (current->getEnum() == Token::NEWLINE)
		{
			current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
		}

		if (expectation->getLevel() == level)
		{
			if (current == nullptr)
			{
				ErrorHandler::getInstance()->addError(Error{ "while statement not completed", ".md", -1, -1, Error::error });
				begin = end;

				break;
			}

			if (current->getEnum() != expectation->getTokenType())
			{
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation->getTokenType(), current->getEnum());
				begin = end;

				break;
			}
			else
			{
				current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
		}
		else if (expectation->getLevel() >= level)
		{
			if (_condition->getCount() == 0)
			{
				shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
				_condition->add(make_shared<DoNothingNode>());
				condition->compile(cTokenList, *current, *current->previous->getPartner(), *_condition, *_condition->getLast());
			}
			else
			{
				shared_ptr<Token> previous = make_shared<Token>(current->previous); // Todo fix tokenizer, will throw error soon
				bodyNode = _body->add(make_shared<DoNothingNode>());

				while (previous->getEnum() != Token::BODY_OPEN)
				{
					previous = make_shared<Token>(previous->previous); // Todo fix tokenizer, will throw error soon
				}
				previous = make_shared<Token>(previous->getPartner()); // Todo fix tokenizer, will throw error soon

				while (current->getLevel() > level)
				{
					shared_ptr<Compiler> compiledBodyPart = factory->createCompileStatement(*current);

					if (compiledBodyPart != nullptr)
					{
						compiledBodyPart->compile(cTokenList, *current, *previous, *_body, *_body->getLast());
					}
					else
					{
						current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
					}
				}
			}
		}
	}
	_conditionBodyMap[_condition] = _body;
	begin = *current;
}

shared_ptr<Compiler> CompileElseIf::create()
{ 
	return make_shared<CompileElseIf>(); 
};

void CompileElseIf::connectLists() 
{
	shared_ptr<ConditionalJumpNode> conditionalJumpNode = make_shared<ConditionalJumpNode>();
	_compiledStatement->add(_condition);
	_compiledStatement->add(conditionalJumpNode);
	_compiledStatement->add(_body);
	_compiledStatement->add(make_shared<DoNothingNode>());
	conditionalJumpNode->setOnTrue(_body->getFirst());
	conditionalJumpNode->setOnFalse(_compiledStatement->getLast());
}