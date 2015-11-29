#include "stdafx.h"
#include "CompileSwitch.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"
#include "TokenExpectation.h"
#include "CompileCondition.h"
#include "ConditionalJumpNode.h"
#include "JumpGotoNode.h"


CompileSwitch::CompileSwitch()
{
	_compiledStatement = new LinkedActionList();
	_condition = new LinkedActionList();
	_bodyDefault = new LinkedActionList();
	_switchNode = new SwitchNode();
}

void CompileSwitch::ConnectLists() {
	_switchNode->switchCondition = _condition;

	std::list<JumpGoToNode*> jumpmap;
	_compiledStatement->add(_switchNode);
	_compiledStatement->add(new DoNothingNode());
	if (_conditionBodyMap.size() > 0) {
		for (auto p = _conditionBodyMap.begin(); p != _conditionBodyMap.end(); ++p)
		{

			if (_conditionBodyMap.size() > 1 || _bodyDefault->Count() > 0) {
				JumpGoToNode* jumpNode = new JumpGoToNode();
				p->second->add(jumpNode);
				jumpmap.push_back(jumpNode);
			}
			_switchNode->jumpMap[p->first] = p->second;
		}

		if (_bodyDefault->Count() > 0) {
			DoNothingNode* secondBodyStart = new DoNothingNode();
			_switchNode->defaultNodeList->add(secondBodyStart);
			_switchNode->defaultNodeList->add(_bodyDefault);
			_switchNode->defaultNodeList->add(new DoNothingNode);
			JumpGoToNode* jumpNode = new JumpGoToNode();
			_switchNode->defaultNodeList->add(jumpNode);
			jumpmap.push_back(jumpNode);
		}
		if (jumpmap.size() > 0) {
			for (auto p : jumpmap) {
				p->setJumpToNode(_compiledStatement->getLast());
			}
		}
	}
	else {
		if (_bodyDefault->Count() > 0) {
			DoNothingNode* secondBodyStart = new DoNothingNode();
			_switchNode->defaultNodeList->add(secondBodyStart);
			_switchNode->defaultNodeList->add(_bodyDefault);
			
			JumpGoToNode* jumpNode = new JumpGoToNode();
			_switchNode->defaultNodeList->add(jumpNode);
			jumpNode->setJumpToNode(_compiledStatement->getLast());
		}
	}
	
}

void CompileSwitch::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	Token* current = &begin;
	int whileLevel = begin.getLevel();
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(whileLevel, Token::SWITCH));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_CLOSE));
	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE) {
			if (current->next != nullptr) {
				current = current->next;
			}
			else
				break;
		}
		if (expectation.Level == whileLevel) {
			if (current == nullptr) {
				ErrorHandler::getInstance()->addError(Error{ "if statement not completed", ".md",-1, -1, Error::error });
				begin = end;
				break;
			}
			if (current->getEnum() != expectation.TokenType) {
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, current->getEnum());
				begin = end;
				break;
			}
			else
				current = current->next;
		}
		else if (expectation.Level >= whileLevel) {
			if (_condition->Count() == 0) {
				if (current->getLevel() >= whileLevel)
				{
					CompileCondition* condition = new CompileCondition();
					_condition->add(new DoNothingNode());
					condition->Compile(cTokenList, *current, *current->previous->getPartner(), *_condition, *_condition->getLast());
					delete condition;
				}
				else 
				{
					ErrorHandler::getInstance()->addError(Error{ "an expression", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, current->getEnum());
					begin = end;
					break;
				}
			}
		}
	}
	CompileCase(cTokenList, *current, end);
	ConnectLists();
	listActionNodes.insertBefore(&actionBefore, _compiledStatement);
	begin = *current;
}

void CompileSwitch::CompileCase(LinkedList& cTokenList, Token& begin, Token& end)
{
	Token* current = &begin;
	int whileLevel = begin.getLevel();
	std::list<LinkedActionList*> conditionList;
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(whileLevel, Token::SWITCH_CASE));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_CLOSE));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1 , Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_CLOSED));
	while (current->getEnum() == Token::NEWLINE) {
		if (current->next != nullptr) {
			current = current->next;
		}
		else
			break;
	}
	while (current->getEnum() == Token::SWITCH_CASE) {
		LinkedActionList* caseCondition = new LinkedActionList();
		LinkedActionList* caseBody = new LinkedActionList();
		for (TokenExpectation expectation : expected)
		{
			while (current->getEnum() == Token::NEWLINE) {
				if (current->next != nullptr) {
					current = current->next;
				}
				else
					break;
			}
			if (expectation.Level == whileLevel) {
				if (current == nullptr) {
					ErrorHandler::getInstance()->addError(Error{ "switch statement not completed", ".md",-1, -1, Error::error });
					begin = end;
					break;
				}
				if (current->getEnum() != expectation.TokenType) {
					if (current->getEnum() == Token::SWITCH_CASE && expectation.TokenType == Token::BODY_OPEN) {
						conditionList.push_back(caseCondition);
						break;
					}
					else {
						ErrorHandler::getInstance()->addError(Error{ "an body", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, current->getEnum());
						begin = end;
						break;
					}
				}
				else
					current = current->next;
			}
			else if (expectation.Level >= whileLevel) {
				if (caseCondition->Count() == 0) {
					if (current->getLevel() > whileLevel) {
						CompileCondition* condition = new CompileCondition();
						caseCondition->add(new DoNothingNode());
						condition->Compile(cTokenList, *current, *current->previous->getPartner(), *caseCondition, *caseCondition->getLast());
						delete condition;
					}
					else {
						ErrorHandler::getInstance()->addError(Error{ "an expression", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, current->getEnum());
						begin = end;
						break;
					}
				}
				else {
					Token* prev = current->previous;
					while (prev->getEnum() != Token::BODY_OPEN) {
						prev = prev->previous;
					}
					prev = prev->getPartner();
					while (current->getLevel() > whileLevel) {
						Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(*current);

						if (compiledBodyPart != nullptr) {
							compiledBodyPart->Compile(cTokenList, *current, *prev, *caseBody, *caseBody->getLast());
						}
						else
						{
							current = current->next;
						}
						delete compiledBodyPart;
					}
				}
			}
		}
		if (caseBody->Count() > 0)
		{
			if (conditionList.size() > 0)
			{
				for (auto p : conditionList)
				{
					_conditionBodyMap[p] = caseBody;
				}
			}
			_conditionBodyMap[caseCondition] = caseBody;
			conditionList.clear();
		}

		while (current->getEnum() == Token::NEWLINE) {
			if (current->next != nullptr) {
				current = current->next;
			}
			else
				break;
		}
	}
	if (current->getEnum() == Token::SWITCH_DEFAULT) {
		CompileDefault(cTokenList, *current, end);
	}
	else {
		current = current->previous;
	}
	begin = *current;
}

void CompileSwitch::CompileDefault(LinkedList& cTokenList, Token& begin, Token& end) {
	Token* current = &begin;
	int whileLevel = begin.getLevel();
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(whileLevel, Token::SWITCH_DEFAULT));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_CLOSED));
	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE) {
			if (current->next != nullptr) {
				current = current->next;
			}
			else
				break;
		}
		if (expectation.Level == whileLevel) {
			if (current == nullptr) {
				ErrorHandler::getInstance()->addError(Error{ "if statement not completed", ".md",-1, -1, Error::error });
				begin = end;
				break;
			}
			if (current->getEnum() != expectation.TokenType) {
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, current->getEnum());
				begin = end;
				break;
			}
			else
				current = current->next;
		}
		else if (expectation.Level >= whileLevel) {
			Token* prev = current->previous;
			while (prev->getEnum() != Token::BODY_OPEN) {
				prev = prev->previous;
			}
			prev = prev->getPartner();
			while (current->getLevel() > whileLevel) {
				Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(*current);

				if (compiledBodyPart != nullptr) {
					compiledBodyPart->Compile(cTokenList, *current, *prev, *_bodyDefault, *_bodyDefault->getLast());
				}
				else
				{
					current = current->next;
				}
				delete compiledBodyPart;
			}
		}
	}
	begin = *current;
}

CompileSwitch::~CompileSwitch()
{
}
