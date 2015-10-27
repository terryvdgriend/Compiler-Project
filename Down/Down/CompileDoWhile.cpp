#include "stdafx.h"
#include "CompileDoWhile.h"
#include "CompileCondition.h"
#include "ConditionalJumpNode.h"
#include "JumpGotoNode.h"
#include "DoNothingNode.h"


CompileDoWhile::CompileDoWhile()
{
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
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_front(TokenExpectation(whileLevel, Token::DO));
	expected.push_front(TokenExpectation(whileLevel, Token::BODY_OPEN));
	expected.push_front(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_front(TokenExpectation(whileLevel, Token::BODY_CLOSED));
	expected.push_front(TokenExpectation(whileLevel, Token::WHILE));
	expected.push_front(TokenExpectation(whileLevel, Token::CONDITION_OPEN));
	expected.push_front(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_front(TokenExpectation(whileLevel, Token::CONDITION_CLOSE));

	for each (TokenExpectation expectation in expected)
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
			if (_condition->Count() == 0){
				CompileCondition* condition{};

				condition->Compile(cTokenList, begin, *begin.previous->getPartner(), *_condition, *_condition->getLast());
				begin = *begin.previous->getPartner();
			}
			else{
				bodyNode = _body->add(new DoNothingNode());
				while (begin.getLevel() > whileLevel){
					Compiler* compiledBodyPart{};
					if (compiledBodyPart != nullptr){
						compiledBodyPart->Compile(cTokenList, begin, *begin.previous->getPartner(), *_body, *_body->getLast());
					}
					else
						begin = *begin.next;
				}
			}
		}
	}
	ConnectLists();
	listActionNodes.add(_compiledStatement);
}

CompileDoWhile::~CompileDoWhile()
{
}
