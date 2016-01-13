#include "stdafx.h"
#include "CompileIf.h"
#include "CompileCondition.h"
#include "CompileComparison.h"
#include "CompileElseIf.h"
#include "CompileFactory.h"
#include "CompileSingleStatement.h"
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

void CompileIf::compile(const shared_ptr<LinkedTokenList>& tokenList, shared_ptr<Token>& begin, shared_ptr<Token>& end,
						shared_ptr<LinkedActionList>& listActionNodes, shared_ptr<ActionNode>& actionBefore)
{
	CompileFactory factory;
	shared_ptr<Token> current = begin;
	int level = begin->getLevel();

	list<TokenExpectation> expected;
	expected.push_back(TokenExpectation(level, IToken::IF));
	expected.push_back(TokenExpectation(level, IToken::CONDITION_OPEN));
	expected.push_back(TokenExpectation(level + 1, IToken::ANY));
	expected.push_back(TokenExpectation(level, IToken::CONDITION_CLOSE));
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
				ErrorHandler::getInstance()->addError(error,expectation.getTokenType(), current->getType());
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
                auto endNode = current->getPrevious()->getPartner();
                auto eBefore = _condition->getLast();
				condition->compile(tokenList, current, endNode, _condition,eBefore);

				if (!multiIndex) 
				{
					current = current->getNext(); 
				}
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
                        auto eBefore = _body->getLast();
						compiledBodyPart->compile(tokenList, current, previous, _body, eBefore);
						
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

		while (current->getType() == IToken::ELSEIF)
		{
			CompileElseIf compileElseIf;
			shared_ptr<LinkedActionList> newBody = make_shared<LinkedActionList>();
			newBody->add(make_shared<DoNothingNode>());
            auto nBody = newBody->getLast();
			compileElseIf.compile(tokenList, current, end, newBody, nBody, _conditionBodyMap);

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
			list<TokenExpectation> expected;
			expected.push_back(TokenExpectation(level, IToken::ELSE));
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
                        auto error = make_shared<Error>("else statement not completed", ".md", -1, -1, ErrorType::ERROR);
						ErrorHandler::getInstance()->addError(error);
						begin = end;

						break;
					}

					if (current->getType() != expectation.getTokenType()) 
					{
                        auto error = make_shared<Error>("", ".md", current->getLineNumber(), current->getPosition(), ErrorType::ERROR);
						ErrorHandler::getInstance()->addError(error,expectation.getTokenType(), current->getType());
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
					bodyNode = _bodyElse->add(make_shared<DoNothingNode>());

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
							compiledBodyPart = make_shared<CompileSingleStatement>();

						if (compiledBodyPart != nullptr) 
						{
                            auto eBefore = _bodyElse->getLast();
							compiledBodyPart->compile(tokenList, current, previous, _bodyElse, eBefore);
							
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
	if (_bodyElse->getCount() == 0 && _conditionBodyMap.size() >= 1)
		current = current->getPrevious();
	listActionNodes->insertBefore(actionBefore, _compiledStatement);
	begin = current;
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