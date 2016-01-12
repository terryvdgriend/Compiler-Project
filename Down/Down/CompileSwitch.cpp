#include "stdafx.h"
#include "CompileSwitch.h"
#include "CompileCondition.h"
#include "CompileComparison.h"
#include "CompileFactory.h"
#include "CompileSingleStatement.h"
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

void CompileSwitch::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
							shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	list<TokenExpectation> expected;
	expected.push_back(TokenExpectation(level, IToken::SWITCH));
	expected.push_back(TokenExpectation(level, IToken::CONDITION_OPEN));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::CONDITION_CLOSE));

	for (TokenExpectation expectation : expected)
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

		if (expectation.getLevel() == level)
		{
			if (current == nullptr) 
			{
                auto error = make_shared<Error>("if statement not completed", ".md", -1, -1, ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error);
				begin = end;

				break;
			}

			if (current->getType() != expectation.getTokenType()) 
			{
                auto error = make_shared<Error>("", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR);
                ErrorHandler::getInstance()->addError(error,
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
			if (_condition->getCount() == 0) 
			{
				if (current->getLevel() >= level)
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
                    auto eNode =current->getPrevious()->getPartner();
                    auto eBefore = _condition->getLast();
					condition->compile(tokenList, current, eNode, _condition, eBefore);

					if (!multiIndex) 
					{ 
						current = current->getNext(); 
					}
				}
				else 
				{
                    auto error = make_shared<Error>("an expression", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR);
                    ErrorHandler::getInstance()->addError(error,
                                                          expectation.getTokenType(), current->getType());
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

void CompileSwitch::compileCase(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end)
{
	CompileFactory factory;
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();
	list<shared_ptr<LinkedActionList>> conditionList;

	list<TokenExpectation> expected;
	expected.push_back(TokenExpectation(level, IToken::SWITCH_CASE));
	expected.push_back(TokenExpectation(level, IToken::CONDITION_OPEN));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::CONDITION_CLOSE));
	expected.push_back(TokenExpectation(level, IToken::BODY_OPEN));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::BODY_CLOSE));

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

		for (TokenExpectation expectation : expected)
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

			if (expectation.getLevel() == level)
			{
				if (current == nullptr) 
				{
                    auto error = make_shared<Error>("switch statement not completed", ".md", -1, -1, ErrorType::ERROR);
					ErrorHandler::getInstance()->addError(error);
					begin = end;

					break;
				}

				if (current->getType() != expectation.getTokenType()) 
				{
					if (current->getType() == IToken::SWITCH_CASE && expectation.getTokenType() == IToken::BODY_OPEN)
					{
						conditionList.push_back(caseCondition);

						break;
					}
					else 
					{
                        auto error = make_shared<Error>("an body", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR);
                        ErrorHandler::getInstance()->addError(error,
                                                              expectation.getTokenType(), current->getType());
						begin = end;

						break;
					}
				}
				else
				{
					current = current->getNext();
				}
			}
			else if (expectation.getLevel() >= level)
			{
				if (caseCondition->getCount() == 0) 
				{
					if (current->getLevel() > level)
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
                        auto eNode = current->getPrevious()->getPartner();
                        auto eBefore = caseCondition->getLast();
						condition->compile(tokenList, current, eNode, caseCondition, eBefore);

						if (!multiIndex) 
						{ 
							current = current->getNext(); 
						}
					}
					else 
					{
                        auto error = make_shared<Error>("an expression", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR);
						ErrorHandler::getInstance()->addError(error,
															  expectation.getTokenType(), current->getType());
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
                            auto eBefore =caseBody->getLast();
							compiledBodyPart->compile(tokenList, current, previous, caseBody, eBefore);

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

void CompileSwitch::compileDefault(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end)
{
	CompileFactory factory;
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	list<TokenExpectation> expected;
	expected.push_back(TokenExpectation(level, IToken::SWITCH_DEFAULT));
	expected.push_back(TokenExpectation(level, IToken::BODY_OPEN));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::BODY_CLOSE));

	for (TokenExpectation expectation : expected)
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

		if (expectation.getLevel() == level)
		{
			if (current == nullptr)
			{
                auto error = make_shared<Error>("if statement not completed", ".md", -1, -1, ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error);
				begin = end;

				break;
			}

			if (current->getType() != expectation.getTokenType())
			{
                auto error = make_shared<Error>("", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error,
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
			shared_ptr<Token> previous = current->getPrevious();

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
                    auto eBefore = _bodyDefault->getLast();
					compiledBodyPart->compile(tokenList, current, previous, _bodyDefault, eBefore);

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
		for (map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>::iterator p = _conditionBodyMap.begin(); p != _conditionBodyMap.end(); ++p)
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