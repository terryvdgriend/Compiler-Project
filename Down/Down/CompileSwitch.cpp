#include "stdafx.h"
#include "CompileSwitch.h"
#include "CompileCondition.h"
#include "CompileFactory.h"
#include "DoNothingNode.h"
#include "JumpGotoNode.h"
#include "TokenExpectation.h"

CompileSwitch::CompileSwitch()
{
	_compiledStatement	= make_shared<LinkedActionList>();
	_condition			= make_shared<LinkedActionList>();
	_bodyDefault		= make_shared<LinkedActionList>();
	_switchNode			= make_shared<SwitchNode>();
}

void CompileSwitch::compile(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
							shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	list<shared_ptr<TokenExpectation>> expected;
	expected.push_back(make_shared<TokenExpectation>(level, IToken::SWITCH));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::CONDITION_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level + 1, IToken::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::CONDITION_CLOSE));

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
				if (current->getLevel() >= level)
				{
					shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
					_condition->add(make_shared<DoNothingNode>());
					condition->compile(tokenList, current, current->getPrevious()->getPartner(), _condition, _condition->getLast());
				}
				else 
				{
					ErrorHandler::getInstance()->addError(make_shared<Error>("an expression", ".md", current->getLevel(), current->getPosition(), ErrorType::error), 
														  expectation->getTokenType(), current->getType());
					begin = end;

					break;
				}
			}
		}
	}
	compileCase(tokenList, current, end);
	connectLists();
	listActionNodes->insertBefore(actionBefore, _compiledStatement);
	begin = current;
}

shared_ptr<Compiler> CompileSwitch::create()
{
	return make_shared<CompileSwitch>();
}

void CompileSwitch::compileCase(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end)
{
	unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();
	list<shared_ptr<LinkedActionList>> conditionList;

	list<shared_ptr<TokenExpectation>> expected;
	expected.push_back(make_shared<TokenExpectation>(level, IToken::SWITCH_CASE));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::CONDITION_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level + 1, IToken::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::CONDITION_CLOSE));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::BODY_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level + 1, IToken::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, IToken::BODY_CLOSED));

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

	while (current->getType() == IToken::SWITCH_CASE)
	{
		shared_ptr<LinkedActionList> caseCondition = make_shared<LinkedActionList>();
		shared_ptr<LinkedActionList> caseBody = make_shared<LinkedActionList>();

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
					ErrorHandler::getInstance()->addError(make_shared<Error>("switch statement not completed", ".md", -1, -1, ErrorType::error));
					begin = end;

					break;
				}

				if (current->getType() != expectation->getTokenType()) 
				{
					if (current->getType() == IToken::SWITCH_CASE && expectation->getTokenType() == IToken::BODY_OPEN)
					{
						conditionList.push_back(caseCondition);

						break;
					}
					else 
					{
						ErrorHandler::getInstance()->addError(make_shared<Error>("an body", ".md", current->getLevel(), current->getPosition(), ErrorType::error),
															  expectation->getTokenType(), current->getType());
						begin = end;

						break;
					}
				}
				else
				{
					current = current->getNext();
				}
			}
			else if (expectation->getLevel() >= level)
			{
				if (caseCondition->getCount() == 0) 
				{
					if (current->getLevel() > level)
					{
						shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
						caseCondition->add(make_shared<DoNothingNode>());
						condition->compile(tokenList, current, current->getPrevious()->getPartner(), caseCondition, caseCondition->getLast());
					}
					else 
					{
						ErrorHandler::getInstance()->addError(make_shared<Error>("an expression", ".md", current->getLevel(), current->getPosition(), ErrorType::error),
															  expectation->getTokenType(), current->getType());
						begin = end;

						break;
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

					while (current->getLevel() > level)
					{
						shared_ptr<Compiler> compiledBodyPart = factory->createCompileStatement(current);

						if (compiledBodyPart != nullptr) 
						{
							compiledBodyPart->compile(tokenList, current, previous, caseBody, caseBody->getLast());
						}
						else
						{
							current = current->getNext();
						}
					}
				}
			}
		}

		if (caseBody->getCount() > 0)
		{
			if (conditionList.size() > 0)
			{
				for (shared_ptr<LinkedActionList> p : conditionList)
				{
					_conditionBodyMap[p] = caseBody;
				}
			}
			_conditionBodyMap[caseCondition] = caseBody;
			conditionList.clear();
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
	}

	if (current->getType() == IToken::SWITCH_DEFAULT)
	{
		compileDefault(tokenList, current, end);
	}
	else 
	{
		current = current->getPrevious();
	}
	begin = current;
}

void CompileSwitch::compileDefault(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end)
{
	unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	list<shared_ptr<TokenExpectation>> expected;
	expected.push_back(make_shared<TokenExpectation>(level, IToken::SWITCH_DEFAULT));
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
			shared_ptr<Token> previous = current->getPrevious();

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
					compiledBodyPart->compile(tokenList, current, previous, _bodyDefault, _bodyDefault->getLast());
				}
				else
				{
					current = current->getNext();
				}
			}
		}
	}
	begin = current;
}

void CompileSwitch::connectLists()
{
	_switchNode->setSwitchConditionList(_condition);

	list<shared_ptr<JumpGoToNode>> jumpMap;
	_compiledStatement->add(_switchNode);
	_compiledStatement->add(make_shared<DoNothingNode>());

	if (_conditionBodyMap.size() > 0) 
	{
		for (auto p = _conditionBodyMap.begin(); p != _conditionBodyMap.end(); ++p)
		{
			if (_conditionBodyMap.size() > 0 || _bodyDefault->getCount() > 0)
			{
				shared_ptr<JumpGoToNode> jumpNode = make_shared<JumpGoToNode>();
				p->second->add(jumpNode);
				jumpMap.push_back(jumpNode);
			}
			_switchNode->getJumpMap()[p->first] = p->second;
		}

		if (_bodyDefault->getCount() > 0) 
		{
			shared_ptr<DoNothingNode> secondBodyStart = make_shared<DoNothingNode>();
			_switchNode->getDefaultNodeList()->add(secondBodyStart);
			_switchNode->getDefaultNodeList()->add(_bodyDefault);
			_switchNode->getDefaultNodeList()->add(make_shared<DoNothingNode>());

			shared_ptr<JumpGoToNode> jumpNode = make_shared<JumpGoToNode>();
			_switchNode->getDefaultNodeList()->add(jumpNode);
			jumpMap.push_back(jumpNode);
		}

		if (jumpMap.size() > 0)
		{
			for (shared_ptr<JumpGoToNode> p : jumpMap)
			{
				p->setJumpToNode(_compiledStatement->getLast());
			}
		}
	}
	else 
	{
		if (_bodyDefault->getCount() > 0) 
		{
			shared_ptr<DoNothingNode> secondBodyStart = make_shared<DoNothingNode>();
			_switchNode->getDefaultNodeList()->add(secondBodyStart);
			_switchNode->getDefaultNodeList()->add(_bodyDefault);

			shared_ptr<JumpGoToNode> jumpNode = make_shared<JumpGoToNode>();
			_switchNode->getDefaultNodeList()->add(jumpNode);
			jumpNode->setJumpToNode(_compiledStatement->getLast());
		}
	}
}