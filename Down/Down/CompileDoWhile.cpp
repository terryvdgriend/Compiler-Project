#include "stdafx.h"
#include "CompileDoWhile.h"
#include "CompileComparison.h"
#include "CompileFactory.h"
#include "CompileSingleStatement.h"
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

void CompileDoWhile::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
							 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	CompileFactory factory;
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	list<TokenExpectation> expected;
	expected.push_back(TokenExpectation(level, IToken::DO));
	expected.push_back(TokenExpectation(level, IToken::BODY_OPEN));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::BODY_CLOSE));
	expected.push_back(TokenExpectation(level, IToken::WHILE));
	expected.push_back(TokenExpectation(level, IToken::CONDITION_OPEN));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::CONDITION_CLOSE));

	for (TokenExpectation expectation : expected)
	{
		while (current->getType() == IToken::NEWLINE)
		{
			current = current->getNext();
		}

		if (expectation.getLevel() == level)
		{
			if (current == nullptr)
			{
				auto error = make_shared<Error>("do while statement not completed", ".md", -1, -1, ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error);
				begin = end;

				break;
			}

			if (current->getType() != expectation.getTokenType())
			{
				
				auto error = make_shared<Error>("", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error, expectation.getTokenType(), current->getType());
				begin = end;

				break;
			}
			else
			{
				current = current->getNext();
			}
		}
		else if (expectation.getLevel() >= level)
		{
			if (_body->getCount() == 0)
			{
				shared_ptr<Token> previous = current->getPrevious();
				_body->add(make_shared<DoNothingNode>());

				while (previous->getType() != IToken::BODY_OPEN)
				{
					previous = previous->getPrevious();
				}
				previous = previous->getPartner();

				while (current->getLevel() > level)
				{
					shared_ptr<Compiler> compiledBodyPart;
					bool multiIndex = false;

					if (current->getType() == IToken::NEWLINE || (current->getNext()->getType() != IToken::BODY_CLOSE && 
						current->getNext()->getType() != IToken::NEWLINE)) 
					{
						compiledBodyPart = factory.createCompileStatement(current);
						multiIndex = true;
					}
					else
					{
						compiledBodyPart = make_shared<CompileSingleStatement>();
					}

					if (compiledBodyPart != nullptr)
					{
                        auto tempToken = _body->getLast();
						compiledBodyPart->compile(tokenList, current, previous, _body, tempToken);

						if (!multiIndex) 
						{ 
							current = current->getNext(); 
						}
					}
					else
					{
						current = current->getNext();
					}
				}
			}
			else
			{
				shared_ptr<Compiler> condition;
				bool multiIndex = false;

				if (current->getNext()->getType() != IToken::CONDITION_CLOSE) 
				{
					condition = make_shared<CompileComparison>();
					multiIndex = true;
				}
				else
				{
					condition = make_shared<CompileSingleStatement>();
				}
                auto endNode =current->getPrevious()->getPartner();
                auto eBefore = _condition->getLast();
				condition->compile(tokenList, current, endNode, _condition, eBefore);

				if (!multiIndex)
				{ 
					current = current->getNext(); 
				}
			}
		}
	}
	connectLists();
	listActionNodes->insertBefore(actionBefore, _compiledStatement);
	begin = current;
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