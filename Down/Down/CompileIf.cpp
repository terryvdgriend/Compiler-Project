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

void CompileIf::compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	//Check if all the tokens are correct
	shared_ptr<Token> current = make_shared<Token>(begin);
	int whileLevel = begin.getLevel();

	unique_ptr<list<shared_ptr<TokenExpectation>>> expected = make_unique<list<shared_ptr<TokenExpectation>>>();
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::IF));
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::CONDITION_OPEN));
	expected->push_back(make_shared<TokenExpectation>(whileLevel + 1, Token::ANY));
	expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::CONDITION_CLOSE));
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

		if (expectation->getLevel() == whileLevel) 
		{
			if (current == nullptr) 
			{
				ErrorHandler::getInstance()->addError(Error{ "if statement not completed", ".md", -1, -1, Error::error });
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
		else if (expectation->getLevel() >= whileLevel) 
		{
			if (_condition->getCount() == 0) 
			{
				shared_ptr<CompileCondition> condition = make_shared<CompileCondition>();
				_condition->add(make_shared<DoNothingNode>());
				condition->compile(cTokenList, *current, *current->previous->getPartner(), *_condition, *_condition->getLast());
			}
			else 
			{
				unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
				shared_ptr<Token> previous = make_shared<Token>(current->previous); // Todo fix tokenizer, will throw error soon
				_body->add(make_shared<DoNothingNode>());

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
	(*_conditionBodyMap)[_condition] = _body;

	if (current != nullptr) 
	{
		// Check if there is an else if-statement 
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

		while (current->getEnum() == Token::ELIF)
		{
			shared_ptr<CompileElseIf> compileElseIf = make_shared<CompileElseIf>();
			shared_ptr<LinkedActionList> newBody = make_shared<LinkedActionList>();
			newBody->add(make_shared<DoNothingNode>());
			compileElseIf->compile(cTokenList, *current, end, *newBody, *newBody->getLast(), *_conditionBodyMap);

			if (current->next != nullptr) 
			{
				current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
			}
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

		//Check if there is an else-statement 
		if (current->getEnum() == Token::ELSE)
		{
			int whileLevel = begin.getLevel();
			unique_ptr<list<shared_ptr<TokenExpectation>>> expected = make_unique<list<shared_ptr<TokenExpectation>>>();
			expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::ELSE));
			expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::BODY_OPEN));
			expected->push_back(make_shared<TokenExpectation>(whileLevel + 1, Token::ANY));
			expected->push_back(make_shared<TokenExpectation>(whileLevel, Token::BODY_CLOSED));

			for (shared_ptr<TokenExpectation> expectation : *expected)	
			{
				while (current->getEnum() == Token::NEWLINE) 
				{
					current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
				}

				if (expectation->getLevel() == whileLevel) 
				{
					if (current == nullptr) 
					{
						ErrorHandler::getInstance()->addError(Error{ "else statement not completed", ".md", -1, -1, Error::error });
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
				else if (expectation->getLevel() >= whileLevel) 
				{
					unique_ptr<CompileFactory> factory = make_unique<CompileFactory>();
					shared_ptr<Token> previous = make_shared<Token>(current->previous); // Todo fix tokenizer, will throw error soon
					bodyNode = _bodyElse->add(make_shared<DoNothingNode>());

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
							compiledBodyPart->compile(cTokenList, *current, *previous, *_bodyElse, *_bodyElse->getLast());
						}
						else
						{
							current = make_shared<Token>(current->next); // Todo fix tokenizer, will throw error soon
						}
					}
				}
			}
			connectLists(); // Build list without else
		}
		else 
		{
			connectLists(); // Build list without else
		}
	}
	else 
	{
		connectLists(); // Build list without else
	}
	listActionNodes.insertBefore(make_shared<ActionNode>(actionBefore), _compiledStatement);
	begin = *current;
}

shared_ptr<Compiler> CompileIf::create()
{
	return make_shared<CompileIf>();
}

void CompileIf::connectLists()
{
	shared_ptr<ConditionalJumpNode> conditionalJumpNode = make_shared<ConditionalJumpNode>();
	unique_ptr<list<shared_ptr<JumpGoToNode>>> jumpmap;

	for (auto p = _conditionBodyMap->begin(); p != _conditionBodyMap->end(); ++p)
	{
		if (p != _conditionBodyMap->begin())
		{
			conditionalJumpNode->setOnFalse(p->first->getFirst());
		}
		conditionalJumpNode = make_shared<ConditionalJumpNode>();
		_compiledStatement->add(p->first);
		_compiledStatement->add(conditionalJumpNode);
		_compiledStatement->add(p->second);

		if (_conditionBodyMap->size() > 1 || _bodyElse->getCount() > 0)
		{
			shared_ptr<JumpGoToNode> jumpNode = make_shared<JumpGoToNode>();
			_compiledStatement->add(jumpNode);
			jumpmap->push_back(jumpNode);
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

	if (jumpmap->size() > 0)
	{
		for (auto p : *jumpmap)
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