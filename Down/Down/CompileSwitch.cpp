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
	expected.push_back(make_shared<TokenExpectation>(level, Token::SWITCH));
	expected.push_back(make_shared<TokenExpectation>(level, Token::CONDITION_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, Token::CONDITION_CLOSE));

	for (shared_ptr<TokenExpectation> expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE) 
		{
			if (current->next != nullptr) 
			{
				current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
			else
			{
				break;
			}
		}

		if (expectation->Level == level)
		{
			if (current == nullptr) 
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("if statement not completed", ".md", -1, -1, ErrorType::error));
				begin = end;

				break;
			}

			if (current->getEnum() != expectation->TokenType) 
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("", ".md", current->getLevel(), current->getPositie(), ErrorType::error), 
													  expectation->TokenType, current->getEnum());
				begin = end;

				break;
			}
			else
			{
				current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
		}
		else if (expectation->Level >= level)
		{
			if (_condition->getCount() == 0) 
			{
				if (current->getLevel() >= level)
				{
					shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
					_condition->add(make_shared<DoNothingNode>());
					condition->compile(tokenList, current, shared_ptr<Token>(current->previous->getPartner()), _condition, _condition->getLast());
				}
				else 
				{
					ErrorHandler::getInstance()->addError(make_shared<Error>("an expression", ".md", current->getLevel(), current->getPositie(), ErrorType::error), 
														  expectation->TokenType, current->getEnum());
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
	expected.push_back(make_shared<TokenExpectation>(level, Token::SWITCH_CASE));
	expected.push_back(make_shared<TokenExpectation>(level, Token::CONDITION_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, Token::CONDITION_CLOSE));
	expected.push_back(make_shared<TokenExpectation>(level, Token::BODY_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, Token::BODY_CLOSED));

	while (current->getEnum() == Token::NEWLINE) 
	{
		if (current->next != nullptr) 
		{
			current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
		}
		else
		{
			break;
		}
	}

	while (current->getEnum() == Token::SWITCH_CASE) 
	{
		shared_ptr<LinkedActionList> caseCondition = make_shared<LinkedActionList>();
		shared_ptr<LinkedActionList> caseBody = make_shared<LinkedActionList>();

		for (shared_ptr<TokenExpectation> expectation : expected)
		{
			while (current->getEnum() == Token::NEWLINE) 
			{
				if (current->next != nullptr) 
				{
					current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
				}
				else
				{
					break;
				}
			}

			if (expectation->Level == level)
			{
				if (current == nullptr) 
				{
					ErrorHandler::getInstance()->addError(make_shared<Error>("switch statement not completed", ".md", -1, -1, ErrorType::error));
					begin = end;

					break;
				}

				if (current->getEnum() != expectation->TokenType) 
				{
					if (current->getEnum() == Token::SWITCH_CASE && expectation->TokenType == Token::BODY_OPEN) 
					{
						conditionList.push_back(caseCondition);

						break;
					}
					else 
					{
						ErrorHandler::getInstance()->addError(make_shared<Error>("an body", ".md", current->getLevel(), current->getPositie(), ErrorType::error),
															  expectation->TokenType, current->getEnum());
						begin = end;

						break;
					}
				}
				else
				{
					current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
				}
			}
			else if (expectation->Level >= level)
			{
				if (caseCondition->getCount() == 0) 
				{
					if (current->getLevel() > level)
					{
						shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
						caseCondition->add(make_shared<DoNothingNode>());
						condition->compile(tokenList, current, shared_ptr<Token>(current->previous->getPartner()), caseCondition, caseCondition->getLast()); // Todo fix tokenizer, will throw error soon
					}
					else 
					{
						ErrorHandler::getInstance()->addError(make_shared<Error>("an expression", ".md", current->getLevel(), current->getPositie(), ErrorType::error),
															  expectation->TokenType, current->getEnum());
						begin = end;

						break;
					}
				}
				else 
				{
					shared_ptr<Token> previous = shared_ptr<Token>(current->previous); // Todo fix tokenizer, will throw error soon

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
							compiledBodyPart->compile(tokenList, current, previous, caseBody, caseBody->getLast());
						}
						else
						{
							current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
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

		while (current->getEnum() == Token::NEWLINE) 
		{
			if (current->next != nullptr) 
			{
				current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
			else
			{
				break;
			}
		}
	}

	if (current->getEnum() == Token::SWITCH_DEFAULT) 
	{
		compileDefault(tokenList, current, end);
	}
	else 
	{
		current = shared_ptr<Token>(current->previous); // Todo fix tokenizer, will throw error soon
	}
	begin = current;
}

void CompileSwitch::compileDefault(shared_ptr<LinkedList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end)
{
	unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	list<shared_ptr<TokenExpectation>> expected;
	expected.push_back(make_shared<TokenExpectation>(level, Token::SWITCH_DEFAULT));
	expected.push_back(make_shared<TokenExpectation>(level, Token::BODY_OPEN));
	expected.push_back(make_shared<TokenExpectation>(level + 1, Token::ANY));
	expected.push_back(make_shared<TokenExpectation>(level, Token::BODY_CLOSED));

	for (shared_ptr<TokenExpectation> expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE)
		{
			if (current->next != nullptr)
			{
				current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
			else
			{
				break;
			}
		}

		if (expectation->Level == level)
		{
			if (current == nullptr)
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("if statement not completed", ".md", -1, -1, ErrorType::error));
				begin = end;

				break;
			}

			if (current->getEnum() != expectation->TokenType)
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("", ".md", current->getLevel(), current->getPositie(), ErrorType::error),
													  expectation->TokenType, current->getEnum());
				begin = end;

				break;
			}
			else
			{
				current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
		}
		else if (expectation->Level >= level)
		{
			shared_ptr<Token> previous = shared_ptr<Token>(current->previous); // Todo fix tokenizer, will throw error soon

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
					compiledBodyPart->compile(tokenList, current, previous, _bodyDefault, _bodyDefault->getLast());
				}
				else
				{
					current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
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