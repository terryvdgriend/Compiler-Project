#include "stdafx.h"
#include "CompileWhile.h"
#include "CompileCondition.h"
#include "ConditionalJumpNode.h"
#include "JumpGotoNode.h"
#include "DoNothingNode.h"

CompileWhile::CompileWhile()
{
}

void CompileWhile::ConnectLists(){
	ConditionalJumpNode* conditionalJumpNode = new ConditionalJumpNode();
	JumpGotoNode* jumpBackNode = new JumpGotoNode();
	_compiledStatement->add(_condition);
	_compiledStatement->add(conditionalJumpNode);
	ActionNode* bodyNothing = _compiledStatement->add(new DoNothingNode);
	_compiledStatement->add(_body);
	_compiledStatement->add(jumpBackNode);
	_compiledStatement->add(new DoNothingNode());
	jumpBackNode->setJumpToNode(_compiledStatement->getFirst());
	conditionalJumpNode->setOnTrue(bodyNothing);
	conditionalJumpNode->setOnFalse(_compiledStatement->getLast());
}

void CompileWhile::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	int whileLevel = begin.getLevel();
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_front(TokenExpectation(whileLevel, Token::WHILE));
	expected.push_front(TokenExpectation(whileLevel, Token::CONDITION_OPEN));
	expected.push_front(TokenExpectation(whileLevel+1, Token::ANY));
	expected.push_front(TokenExpectation(whileLevel, Token::CONDITION_CLOSE));
	expected.push_front(TokenExpectation(whileLevel, Token::BODY_OPEN));
	expected.push_front(TokenExpectation(whileLevel+1, Token::ANY));
	expected.push_front(TokenExpectation(whileLevel, Token::BODY_CLOSED));

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
			if (_condition->getFirst() == nullptr){
				CompileCondition* condition{};

				condition->Compile(cTokenList, begin, *begin.previous->getPartner(), *_condition, *_condition->getFirst());
				begin = *begin.previous->getPartner();
			}
			else{
				while (begin.getLevel() > whileLevel){
					Compiler* compiledBodyPart{};
					if (compiledBodyPart != nullptr){
						compiledBodyPart->Compile(cTokenList, begin, *begin.previous->getPartner(), *_body, *_body->getFirst());
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

CompileWhile::~CompileWhile()
{
}
