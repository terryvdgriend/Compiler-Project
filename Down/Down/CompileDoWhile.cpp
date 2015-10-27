#include "stdafx.h"
#include "CompileDoWhile.h"
#include "CompileCondition.h"
#include "ConditionalJumpNode.h"
#include "JumpGotoNode.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"


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
	int whileLevel = begin.getLevel();
	std::list<TokenExpectations> expected = std::list<TokenExpectations>();
	expected.push_front(TokenExpectations(whileLevel, Token::DO));
	expected.push_front(TokenExpectations(whileLevel, Token::BODY_OPEN));
	expected.push_front(TokenExpectations(whileLevel + 1, Token::ANY));
	expected.push_front(TokenExpectations(whileLevel, Token::BODY_CLOSED));
	expected.push_front(TokenExpectations(whileLevel, Token::WHILE));
	expected.push_front(TokenExpectations(whileLevel, Token::CONDITION_OPEN));
	expected.push_front(TokenExpectations(whileLevel + 1, Token::ANY));
	expected.push_front(TokenExpectations(whileLevel, Token::CONDITION_CLOSE));

	for each (TokenExpectations expectation in expected)
	{
		if (expectation.Level == whileLevel){
			if (begin.getEnum() != expectation.TokenType){
				throw exception("Dingen enzo");
				break;
			}
			else
				begin = *begin.next;
		}
		else if (expectation.Level >= whileLevel){
			if (_body->Count() == 0){
				bodyNode = _body->add(new DoNothingNode());
				while (begin.getLevel() > whileLevel){
					Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(begin.getEnum());
					if (compiledBodyPart != nullptr){
						compiledBodyPart->Compile(cTokenList, begin, *begin.previous->getPartner(), *_body, *_body->getLast());
					}
					else
						begin = *begin.next;
				}
			}
			else{
				CompileCondition* condition = new CompileCondition();

				condition->Compile(cTokenList, begin, *begin.previous->getPartner(), *_condition, *_condition->getLast());
				begin = *begin.previous->getPartner();
				
			}
		}
	}
	ConnectLists();
	listActionNodes.add(_compiledStatement);
}

CompileDoWhile::~CompileDoWhile()
{
}
