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

void CompileElseIf::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end, shared_ptr<LinkedActionList>& listActionNodes,
							shared_ptr<ActionNode>& actionBefore)
{
	// No implementation - specific implementation below
}

void CompileElseIf::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end, shared_ptr<LinkedActionList>& listActionNodes,
							shared_ptr<ActionNode>& actionBefore, map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>& _conditionBodyMap)
{
	CompileFactory factory;
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	list<shared_ptr<TokenExpectation>> expected;
	expected.push_back(make_shared<TokenExpectation>(level, IToken::ELIF));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::CONDITION_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level + 1, IToken::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::CONDITION_CLOSE));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::BODY_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level + 1, IToken::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::BODY_CLOSED));

	for (shared_ptr<TokenExpectation> expectation : expected)
	{
		while (current->getType() == IToken::NEWLINE)
		{
			current = current->getNext();
		}

		if (expectation->getLevel() == level)
		{
			if (current == nullptr)
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("while statement not completed", ".md", -1, -1, ErrorType::error));
				begin = end;

				break;
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
		else if (expectation->getLevel() >= level)
		{
			if (_condition->getCount() == 0)
			{
				shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
				_condition->add(make_shared<DoNothingNode>());
				condition->compile(tokenList, current, current->getPrevious()->getPartner(), _condition, _condition->getLast());
			}
			else
			{
				shared_ptr<Token> previous = current->getPrevious();
				bodyNode = _body->add(make_shared<DoNothingNode>());

				while (previous->getType() != IToken::BODY_OPEN)
				{
					previous = previous->getPrevious();
				}
				previous = previous->getPartner();

				while (current->getLevel() > level)
				{
					shared_ptr<Compiler> compiledBodyPart = factory.createCompileStatement(current);

					if (compiledBodyPart != nullptr)
					{
						compiledBodyPart->compile(tokenList, current, previous, _body, _body->getLast());
					}
					else
					{
						current = current->getNext(); 
					}
				}
			}
		}
	}
	_conditionBodyMap[_condition] = _body;
	begin = current;
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