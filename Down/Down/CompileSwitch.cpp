#include "stdafx.h"
#include "CompileSwitch.h"
#include "CompileCondition.h"
#include "CompileFactory.h"
#include "ConditionalJumpNode.h"
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

void CompileSwitch::compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	shared_ptr<Token> current = make_shared<Token>(begin); // Todo fix tokenizer, will throw error soon
	int whileLevel = begin.getLevel();

	unique_ptr<list<shared_ptr<TokenExpectation>>> expected = make_unique<list<shared_ptr<TokenExpectation>>>();
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::SWITCH));
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::CONDITION_OPEN));
	expected->push_back(make_shared<TokenExpectation>(whileLevel + 1, Token::ANY));
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::CONDITION_CLOSE));

	for (shared_ptr<TokenExpectation> expectation : *expected)
	{
		while (current->getEnum() == Token::NEWLINE) 
		{
			if (current->next != nullptr) 
			{
				current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
			else
			{
				break;
			}
		}

		if (expectation->Level == whileLevel) 
		{
			if (current == nullptr) 
			{
				ErrorHandler::getInstance()->addError(Error{ "if statement not completed", ".md", -1, -1, Error::error });
				begin = end;

				break;
			}

			if (current->getEnum() != expectation->TokenType) 
			{
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation->TokenType, current->getEnum());
				begin = end;

				break;
			}
			else
			{
				current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
		}
		else if (expectation->Level >= whileLevel) 
		{
			if (_condition->getCount() == 0) 
			{
				if (current->getLevel() >= whileLevel)
				{
					shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
					_condition->add(make_shared<DoNothingNode>());
					condition->Compile(cTokenList, *current, *current->previous->getPartner(), *_condition, *_condition->getLast());
				}
				else 
				{
					ErrorHandler::getInstance()->addError(Error{ "an expression", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation->TokenType, current->getEnum());
					begin = end;

					break;
				}
			}
		}
	}
	compileCase(cTokenList, *current, end);
	connectLists();
	listActionNodes.insertBefore(make_shared<ActionNode>(actionBefore), _compiledStatement);
	begin = *current;
}

shared_ptr<Compiler> CompileSwitch::create()
{
	return make_shared<CompileSwitch>();
}

void CompileSwitch::compileCase(LinkedList& cTokenList, Token& begin, Token& end)
{
	// Check if all the tokens are correct
	shared_ptr<Token> current = make_shared<Token>(begin);
	int whileLevel = begin.getLevel();
	unique_ptr<list<shared_ptr<LinkedActionList>>> conditionList = make_unique<list<shared_ptr<LinkedActionList>>>();

	unique_ptr<list<shared_ptr<TokenExpectation>>> expected = make_unique<list<shared_ptr<TokenExpectation>>>();
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::SWITCH_CASE));
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::CONDITION_OPEN));
	expected->push_back(make_shared<TokenExpectation>(whileLevel + 1, Token::ANY));
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::CONDITION_CLOSE));
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::BODY_OPEN));
	expected->push_back(make_shared<TokenExpectation>(whileLevel + 1, Token::ANY));
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::BODY_CLOSED));

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

		for (shared_ptr<TokenExpectation> expectation : *expected)
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

			if (expectation->Level == whileLevel) 
			{
				if (current == nullptr) 
				{
					ErrorHandler::getInstance()->addError(Error{ "switch statement not completed", ".md", -1, -1, Error::error });
					begin = end;

					break;
				}

				if (current->getEnum() != expectation->TokenType) 
				{
					if (current->getEnum() == Token::SWITCH_CASE && expectation->TokenType == Token::BODY_OPEN) 
					{
						conditionList->push_back(caseCondition);

						break;
					}
					else 
					{
						ErrorHandler::getInstance()->addError(Error{ "an body", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation->TokenType, current->getEnum());
						begin = end;

						break;
					}
				}
				else
				{
					current = shared_ptr<Token>(current->next); // Todo fix tokenizer, will throw error soon
				}
			}
			else if (expectation->Level >= whileLevel) 
			{
				if (caseCondition->getCount() == 0) 
				{
					if (current->getLevel() > whileLevel) 
					{
						shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
						caseCondition->add(make_shared<DoNothingNode>());
						condition->Compile(cTokenList, *current, *current->previous->getPartner(), *caseCondition, *caseCondition->getLast());
					}
					else 
					{
						ErrorHandler::getInstance()->addError(Error{ "an expression", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation->TokenType, current->getEnum());
						begin = end;

						break;
					}
				}
				else 
				{
					unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
					shared_ptr<Token> previous = make_shared<Token>(current->previous); // Todo fix tokenizer, will throw error soon

					while (previous->getEnum() != Token::BODY_OPEN)
					{
						previous = make_shared<Token>(previous->previous); // Todo fix tokenizer, will throw error soon
					}
					previous = make_shared<Token>(previous->getPartner()); // Todo fix tokenizer, will throw error soon

					while (current->getLevel() > whileLevel) 
					{
						shared_ptr<Compiler> compiledBodyPart = factory->createCompileStatement(*current);

						if (compiledBodyPart != nullptr) 
						{
							compiledBodyPart->compile(cTokenList, *current, *previous, *caseBody, *caseBody->getLast());
						}
						else
						{
							current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
						}
					}
				}
			}
		}

		if (caseBody->getCount() > 0)
		{
			if (conditionList->size() > 0)
			{
				for (auto p : *conditionList)
				{
					(*_conditionBodyMap)[p] = caseBody;
				}
			}
			(*_conditionBodyMap)[caseCondition] = caseBody;
			conditionList->clear();
		}

		while (current->getEnum() == Token::NEWLINE) 
		{
			if (current->next != nullptr) 
			{
				current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
			else
			{
				break;
			}
		}
	}

	if (current->getEnum() == Token::SWITCH_DEFAULT) 
	{
		compileDefault(cTokenList, *current, end);
	}
	else 
	{
		current = make_shared<Token>(current->previous); // Todo fix tokenizer, will throw error soon
	}
	begin = *current;
}

void CompileSwitch::compileDefault(LinkedList& cTokenList, Token& begin, Token& end)
{
	// Check if all the tokens are correct
	shared_ptr<Token> current = make_shared<Token>(begin);
	int whileLevel = begin.getLevel();

	unique_ptr<list<shared_ptr<TokenExpectation>>> expected = make_unique<list<shared_ptr<TokenExpectation>>>();
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::SWITCH_DEFAULT));
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::BODY_OPEN));
	expected->push_back(make_shared<TokenExpectation>(whileLevel + 1, Token::ANY));
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::BODY_CLOSED));

	for (shared_ptr<TokenExpectation> expectation : *expected)
	{
		while (current->getEnum() == Token::NEWLINE)
		{
			if (current->next != nullptr)
			{
				current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
			else
			{
				break;
			}
		}

		if (expectation->Level == whileLevel)
		{
			if (current == nullptr)
			{
				ErrorHandler::getInstance()->addError(Error{ "if statement not completed", ".md", -1, -1, Error::error });
				begin = end;

				break;
			}

			if (current->getEnum() != expectation->TokenType)
			{
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation->TokenType, current->getEnum());
				begin = end;

				break;
			}
			else
			{
				current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
		}
		else if (expectation->Level >= whileLevel)
		{
			unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
			shared_ptr<Token> previous = make_shared<Token>(current->previous); // Todo fix tokenizer, will throw error soon

			while (previous->getEnum() != Token::BODY_OPEN)
			{
				previous = make_shared<Token>(previous->previous); // Todo fix tokenizer, will throw error soon
			}
			previous = make_shared<Token>(previous->getPartner()); // Todo fix tokenizer, will throw error soon

			while (current->getLevel() > whileLevel)
			{
				shared_ptr<Compiler> compiledBodyPart = factory->createCompileStatement(*current);

				if (compiledBodyPart != nullptr)
				{
					compiledBodyPart->compile(cTokenList, *current, *previous, *_bodyDefault, *_bodyDefault->getLast());
				}
				else
				{
					current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
				}
			}
		}
	}
	begin = *current;
}

void CompileSwitch::connectLists()
{
	_switchNode->setSwitchConditionList(_condition);

	unique_ptr<list<shared_ptr<JumpGoToNode>>> jumpMap = make_unique<list<shared_ptr<JumpGoToNode>>>();
	_compiledStatement->add(_switchNode);
	_compiledStatement->add(make_shared<DoNothingNode>());

	if (_conditionBodyMap->size() > 0) 
	{
		for (auto p = _conditionBodyMap->begin(); p != _conditionBodyMap->end(); ++p)
		{
			if (_conditionBodyMap->size() > 0 || _bodyDefault->getCount() > 0)
			{
				shared_ptr<JumpGoToNode> jumpNode = make_shared<JumpGoToNode>();
				p->second->add(jumpNode);
				jumpMap->push_back(jumpNode);
			}
			(*_switchNode->getJumpMap())[p->first] = p->second;
		}

		if (_bodyDefault->getCount() > 0) 
		{
			shared_ptr<DoNothingNode> secondBodyStart = make_shared<DoNothingNode>();
			_switchNode->getDefaultNodeList()->add(secondBodyStart);
			_switchNode->getDefaultNodeList()->add(_bodyDefault);
			_switchNode->getDefaultNodeList()->add(make_shared<DoNothingNode>());

			shared_ptr<JumpGoToNode> jumpNode = make_shared<JumpGoToNode>();
			_switchNode->getDefaultNodeList()->add(jumpNode);
			jumpMap->push_back(jumpNode);
		}

		if (jumpMap->size() > 0)
		{
			for (auto p : *jumpMap)
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