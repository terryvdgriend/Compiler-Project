#include "stdafx.h"
#include "CompileDoWhile.h"
#include "CompileCondition.h"
#include "ConditionalJumpNode.h"
#include "JumpGoToNode.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"
#include "TokenExpectation.h"


CompileDoWhile::CompileDoWhile()
{
	_compiledStatement = new LinkedActionList();
	_condition = new LinkedActionList();
	_body = new LinkedActionList();
	_compiledStatement->add(new DoNothingNode());
}

void CompileDoWhile::ConnectLists(){
	ConditionalJumpNode* conditionalJumpNode = new ConditionalJumpNode();
	_compiledStatement->add(_body);
	_compiledStatement->add(_condition);
	_compiledStatement->add(conditionalJumpNode);
	_compiledStatement->add(new DoNothingNode());
	conditionalJumpNode->setOnTrue(_body->getFirst());
	conditionalJumpNode->setOnFalse(_compiledStatement->getLast());
}

void CompileDoWhile::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	Token* current = &begin;
	int whileLevel = begin.getLevel();
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(whileLevel, Token::DO));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_CLOSED));
	expected.push_back(TokenExpectation(whileLevel, Token::WHILE));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_CLOSE));

	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE){
			current = current->next;
		}
		if (expectation.Level == whileLevel){
			if (current == nullptr){
				ErrorHandler::getInstance()->addError(Error{ "do while statement not completed", ".md", -1, -1, Error::error });
				begin = end;
				break;
			}
			if (current->getEnum() != expectation.TokenType){
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, current->getEnum());
				begin = end;
				break;
			}
			else
				current = current->next;
		}
		else if (expectation.Level >= whileLevel){
			if (_body->Count() == 0){
				bodyNode = _body->add(new DoNothingNode());
				Token* prev = current->previous;
				while (prev->getEnum() != Token::BODY_OPEN){
					prev = prev->previous;
				}
				prev = prev->getPartner();
				while (current->getLevel() > whileLevel){
					Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(*current);
					if (compiledBodyPart != nullptr){
						compiledBodyPart->Compile(cTokenList, *current, *prev, *_body, *_body->getLast());
					}
					else
					{
						current = current->next;
					}
					delete compiledBodyPart;
				}
			}
			else{
				CompileCondition* condition = new CompileCondition();
				condition->Compile(cTokenList, *current, *current->previous->getPartner(), *_condition, *_condition->getLast());
				delete condition;
			}
		}
	}
	ConnectLists();
	listActionNodes.add(_compiledStatement);
	begin = *current;
}

CompileDoWhile::~CompileDoWhile()
{
	delete bodyNode;
	delete _body;
	delete _condition;
	delete _compiledStatement;
}
