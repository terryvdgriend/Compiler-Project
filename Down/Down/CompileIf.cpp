#include "stdafx.h"
#include "CompileIf.h"
#include "CompileCondition.h"
#include "CompileElseIf.h"
#include "CompileFactory.h"
#include "ConditionalJumpNode.h"
#include "DoNothingNode.h"
#include "JumpGotoNode.h"
#include "TokenExpectation.h"

CompileIf::CompileIf()
{
	_compiledStatement	= make_shared<LinkedActionList>();
	_condition			= make_shared<LinkedActionList>();
	_body				= make_shared<LinkedActionList>();
	_bodyElse			= make_shared<LinkedActionList>();
	_compiledStatement->add(make_shared<DoNothingNode>());
}

void CompileIf::compile(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
						shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	list<shared_ptr<TokenExpectation>> expected;
	expected.push_back(make_shared<TokenExpectation>(level, IToken::IF));
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
			if (current->getNext() != nullptr) 
			{
				current = current->getNext();
			}
			else
			{
				break;
			}
		}

		if (expectation->getLevel() == level)
		{
			if (current == nullptr) 
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("if statement not completed", ".md", -1, -1, ErrorType::error));
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
				_body->add(make_shared<DoNothingNode>());

				while (previous->getType() != IToken::BODY_OPEN)
				{
					previous = previous->getPrevious();
				}
				previous = previous->getPartner();

				while (current->getLevel() > level)
				{
					shared_ptr<Compiler> compiledBodyPart = factory->createCompileStatement(current);

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

	if (current != nullptr) 
	{
		// Check if there is an else if-statement 
		while (current->getType() == IToken::NEWLINE)
		{
			if (current->getNext() != nullptr) 
			{
				current = current->getNext();
			}
			else
			{
				break;
			}
		}

		while (current->getType() == IToken::ELIF)
		{
			shared_ptr<CompileElseIf> compileElseIf = make_shared<CompileElseIf>();
			shared_ptr<LinkedActionList> newBody = make_shared<LinkedActionList>();
			newBody->add(make_shared<DoNothingNode>());
			compileElseIf->compile(tokenList, current, end, newBody, newBody->getLast(), _conditionBodyMap);

			if (current->getNext() != nullptr) 
			{
				current = current->getNext();
			}
		}

		while (current->getType() == IToken::NEWLINE)
		{
			if (current->getNext() != nullptr) 
			{
				current = current->getNext();
			}
			else
			{
				break;
			}
		}

		//Check if there is an else-statement 
		if (current->getType() == IToken::ELSE)
		{
			int level = begin->getLevel();
			list<shared_ptr<TokenExpectation>> expected;
			expected.push_back(make_shared<TokenExpectation>(level, IToken::ELSE));
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
						ErrorHandler::getInstance()->addError(make_shared<Error>("else statement not completed", ".md", -1, -1, ErrorType::error));
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
					shared_ptr<Token> previous = current->getPrevious();
					bodyNode = _bodyElse->add(make_shared<DoNothingNode>());

					while (previous->getType() != IToken::BODY_OPEN)
					{
						previous = previous->getPrevious();
					}
					previous = previous->getPartner();

					while (current->getLevel() > level)
					{
						shared_ptr<Compiler> compiledBodyPart = factory->createCompileStatement(current);

						if (compiledBodyPart != nullptr) 
						{
							compiledBodyPart->compile(tokenList, current, previous, _bodyElse, _bodyElse->getLast());
						}
						else
						{
							current = current->getNext();
						}
					}
				}
			}
			connectLists(); // Build list without the else
		}
		else 
		{
			connectLists(); // Build list without the else
		}
	}
	else 
	{
		connectLists(); // Build list without theelse
	}
	listActionNodes->insertBefore(actionBefore, _compiledStatement);
	begin = current;
}

shared_ptr<Compiler> CompileIf::create()
{
	return make_shared<CompileIf>();
}

void CompileIf::connectLists()
{
	shared_ptr<ConditionalJumpNode> conditionalJumpNode = make_shared<ConditionalJumpNode>();
	list<shared_ptr<JumpGoToNode>> jumpMap;

	for (map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>::iterator p = _conditionBodyMap.begin(); p != _conditionBodyMap.end(); ++p)
	{
		if (p != _conditionBodyMap.begin())
		{
			conditionalJumpNode->setOnFalse(p->first->getFirst());
		}
		conditionalJumpNode = make_shared<ConditionalJumpNode>();
		_compiledStatement->add(p->first);
		_compiledStatement->add(conditionalJumpNode);
		_compiledStatement->add(p->second);

		if (_conditionBodyMap.size() > 1 || _bodyElse->getCount() > 0)
		{
			shared_ptr<JumpGoToNode> jumpNode = make_shared<JumpGoToNode>();
			_compiledStatement->add(jumpNode);
			jumpMap.push_back(jumpNode);
		}
		_compiledStatement->add(make_shared<DoNothingNode>());
		conditionalJumpNode->setOnTrue(p->second->getFirst());
	}

	if (_bodyElse->getCount() > 0)
	{
		shared_ptr<DoNothingNode> secondBodyStart = make_shared<DoNothingNode>();
		_compiledStatement->add(secondBodyStart);
		_compiledStatement->add(_bodyElse);
		_compiledStatement->add(make_shared<DoNothingNode>());
		conditionalJumpNode->setOnFalse(secondBodyStart);
	}
	else
	{
		conditionalJumpNode->setOnFalse(_compiledStatement->getLast());
	}

	if (jumpMap.size() > 0)
	{
		for (shared_ptr<JumpGoToNode> p : jumpMap)
		{
			p->setJumpToNode(_compiledStatement->getLast());
		}
	}
}

void CompileIf::connectListsWithElse()
{
	shared_ptr<ConditionalJumpNode> conditionalJumpNode = make_shared<ConditionalJumpNode>();
	shared_ptr<JumpGoToNode> jumpOverSecondBody = make_shared<JumpGoToNode>();
	shared_ptr<DoNothingNode> secondBodyStart = make_shared<DoNothingNode>();

	_compiledStatement->add(_condition);
	_compiledStatement->add(conditionalJumpNode);
	_compiledStatement->add(_body);
	_compiledStatement->add(jumpOverSecondBody);
	_compiledStatement->add(secondBodyStart);
	_compiledStatement->add(_bodyElse);
	_compiledStatement->add(make_shared<DoNothingNode>());
	jumpOverSecondBody->setJumpToNode(_compiledStatement->getLast());
	conditionalJumpNode->setOnTrue(_body->getFirst());
	conditionalJumpNode->setOnFalse(secondBodyStart);
}