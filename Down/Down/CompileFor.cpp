#include "stdafx.h"
#include "CompileFor.h"
#include "CompileCondition.h"
#include "CompileFactory.h"
#include "CompileSingleStatement.h"
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

void CompileFor::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
						 shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	CompileFactory factory;
	shared_ptr<Token> current = begin;
	shared_ptr<Token> conClose = nullptr;
	int level = begin->getLevel();

	list<TokenExpectation> expected;
	expected.push_back(TokenExpectation(level, IToken::FOR));
	expected.push_back(TokenExpectation(level, IToken::CONDITION_OPEN));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level + 1, IToken::AND_PARA));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level + 1, IToken::AND_PARA));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::CONDITION_CLOSE));
	expected.push_back(TokenExpectation(level, IToken::BODY_OPEN));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::BODY_CLOSE));

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
				ErrorHandler::getInstance()->addError(make_shared<Error>("for statement not completed", ".md", -1, -1, ErrorType::ERROR));
				begin = end;

				break;
			}

			if (current->getType() == IToken::CONDITION_OPEN)
			{
				conClose = current->getPartner();
			}

			if (current->getType() != expectation.getTokenType())
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("", ".md", current->getLevel(), current->getPosition(), ErrorType::ERROR),
													  expectation.getTokenType(), current->getType());
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
			if (current->getType() == expectation.getTokenType() && current->getType() == IToken::AND_PARA)
			{
				current = current->getNext();

				continue;
			}

			if (_declaration->getCount() == 0)
			{
				shared_ptr<Token> next = current->getPrevious();

				while (next->getType() != IToken::AND_PARA)
				{
					next = next->getNext();
				}

				// This means the declaration is empty
				if (next->getPrevious()->getType() == IToken::CONDITION_OPEN)
				{
					ErrorHandler::getInstance()->addError(make_shared<Error>("For statement has no declaration!", ".md", current->getLineNumber(), 
														  current->getPosition(), ErrorType::ERROR));
					begin = end;

					return;
				}
				else 
				{
					// Compile the first part of the for-loop
					shared_ptr<Compiler> compiledBodyPart;
					bool multiIndex = false;

					if (current->getNext()->getType() != IToken::AND_PARA)
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
						compiledBodyPart->compile(tokenList, current, next, _declaration, _declaration->getLast());

						// If the list still is empty, fill with an DoNothingNode 
						if (_declaration->getCount() == 0)
						{
							_declaration->insertLast(make_shared<DoNothingNode>());
						}

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
			else if (_condition->getCount() == 0)
			{
				shared_ptr<Token> next = current->getNext();

				while (next->getType() != IToken::AND_PARA)
				{
					next = next->getNext();
				}
				shared_ptr<Compiler> condition;
				bool multiIndex = false;

				if (current->getNext()->getType() != IToken::AND_PARA) 
				{
					condition = make_shared<CompileCondition>();
					multiIndex = true;
				}
				else
				{
					condition = make_shared<CompileSingleStatement>();
				}
				condition->compile(tokenList, current, next, _condition, _condition->getLast());

				if (!multiIndex) 
				{
					current = current->getNext(); 
				}

				// If condition still is empty, throw error (we need a condition)
				if (_condition->getCount() == 0) 
				{
					ErrorHandler::getInstance()->addError(make_shared<Error>("For statement has no condition!", ".md", current->getLineNumber(), 
														  current->getPosition(), ErrorType::ERROR));
					begin = end;

					break;
				}
			}
			else if (_increment->getCount() == 0)
			{
				if (current->getType() == IToken::CONDITION_CLOSE) 
				{
					ErrorHandler::getInstance()->addError(make_shared<Error>("For statement has no increment!", ".md", current->getLineNumber(), 
														  current->getPosition(), ErrorType::ERROR));
					begin = end;

					return;
				}

				// Compile the last part of the for-loop
				shared_ptr<Compiler> compiledBodyPart;
				bool multiIndex = false;

				if (current->getNext()->getType() != IToken::CONDITION_CLOSE) 
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
					compiledBodyPart->compile(tokenList, current, conClose, _increment, _increment->getLast());

					// If the list still is empty, fill with an DoNothingNode 
					if (_declaration->getCount() == 0)
					{
						_declaration->insertLast(make_shared<DoNothingNode>());
					}

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
			else
			{
				shared_ptr<Token> previous = current->getPrevious();

				while (previous->getType() != IToken::BODY_OPEN)
				{
					previous = previous->getPrevious();
				}
				previous = previous->getPartner();
				_body->add(make_shared<DoNothingNode>());

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
						compiledBodyPart->compile(tokenList, current, previous, _body, _body->getLast());
						
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
		}
	}
	connectLists();
	listActionNodes->insertBefore(actionBefore, _compiledStatement);
	begin = current;
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