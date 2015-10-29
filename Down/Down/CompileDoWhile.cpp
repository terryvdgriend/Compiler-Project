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
		if (expectation.Level == whileLevel){
			if (current == nullptr){
				ErrorHandler::getInstance()->addError(Error{ "do while statement not completed", ".md", -1, -1, Error::error });
				begin = end;
				break;
			}
			if (current == nullptr || current->getEnum() != expectation.TokenType){
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
				while (current->getLevel() > whileLevel){
					Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(current->getEnum());
					if (compiledBodyPart != nullptr){
						compiledBodyPart->Compile(cTokenList, *current, *current->previous->getPartner(), *_body, *_body->getLast());
						current = current->previous->getPartner();
						begin = *current;
					}
					else
					{
						ErrorHandler::getInstance()->addError("Incorrect syntax ", current);
						current = current->next;
					}
					delete compiledBodyPart;
				}
			}
			else{
				CompileCondition* condition = new CompileCondition();
				condition->Compile(cTokenList, *current, *current->previous->getPartner(), *_condition, *_condition->getLast());
				current = current->previous->getPartner();
				begin = *current;
				delete condition;
			}
		}
	}
	ConnectLists();
	listActionNodes.add(_compiledStatement);
}

CompileDoWhile::~CompileDoWhile()
{
	delete bodyNode;
	delete _body;
	delete _condition;
	delete _compiledStatement;
}
