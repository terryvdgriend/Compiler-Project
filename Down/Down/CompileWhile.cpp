#include "stdafx.h"
#include "CompileWhile.h"
#include "CompileCondition.h"
#include "ConditionalJumpNode.h"
#include "JumpGotoNode.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"

CompileWhile::CompileWhile()
{
	_compiledStatement = new LinkedActionList();
	_condition = new LinkedActionList();
	_body = new LinkedActionList();
	_compiledStatement->add(new DoNothingNode());
}

void CompileWhile::ConnectLists(){
	ConditionalJumpNode* conditionalJumpNode = new ConditionalJumpNode();
	JumpGotoNode* jumpBackNode = new JumpGotoNode();
	_compiledStatement->add(_condition);
	_compiledStatement->add(conditionalJumpNode);
	_compiledStatement->add(_body);
	_compiledStatement->add(jumpBackNode);
	_compiledStatement->add(new DoNothingNode());
	jumpBackNode->setJumpToNode(_compiledStatement->getFirst());
	conditionalJumpNode->setOnTrue(_body->getFirst());
	conditionalJumpNode->setOnFalse(_compiledStatement->getLast());
}

void CompileWhile::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	int whileLevel = begin.getLevel();
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(whileLevel, Token::WHILE));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_CLOSE));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_CLOSED));

    for(TokenExpectation expectation: expected)
	//for each (TokenExpectation expectation in expected)
	{
		if (expectation.Level == whileLevel){
			if (begin.getEnum() != expectation.TokenType){
				//throw exception("Dingen enzo"); WERKT NIET?
				break;
			}
			else
				begin = *begin.next;
		}
		else if (expectation.Level >= whileLevel){
			if (_condition->Count() == 0){
				CompileCondition* condition = new CompileCondition();
				_condition->add(new DoNothingNode());
				condition->Compile(cTokenList, begin, *begin.previous->getPartner(), *_condition, *_condition->getLast());
				begin = *begin.previous->getPartner();
			}
			else{
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
		}
	}
	ConnectLists();
	listActionNodes.add(_compiledStatement);
}

CompileWhile::~CompileWhile()
{
}
