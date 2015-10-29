#include "stdafx.h"
#include "CompileElseIf.h"
#include "CompileCondition.h"
#include "ConditionalJumpNode.h"
#include "JumpGotoNode.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"
#include "TokenExpectation.h"

CompileElseIf::CompileElseIf()
{
	_compiledStatement = new LinkedActionList();
	_condition = new LinkedActionList();
	_body = new LinkedActionList();
	_compiledStatement->add(new DoNothingNode());
}

void CompileElseIf::ConnectLists(){
	ConditionalJumpNode* conditionalJumpNode = new ConditionalJumpNode();
	_compiledStatement->add(_condition);
	_compiledStatement->add(conditionalJumpNode);
	_compiledStatement->add(_body);
	_compiledStatement->add(new DoNothingNode());
	conditionalJumpNode->setOnTrue(_body->getFirst());
	conditionalJumpNode->setOnFalse(_compiledStatement->getLast());
}

void CompileElseIf::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	//Check if all the tokens are correct
	Token* current = &begin;
	int whileLevel = begin.getLevel();
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(whileLevel, Token::ELIF));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_CLOSE));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_CLOSED));

	for (TokenExpectation expectation : expected)
		//for each (TokenExpectation expectation in expected)
	{
		if (expectation.Level == whileLevel){
			if (current->getEnum() != expectation.TokenType){
				//TODO ERROR Mike-u
				begin = end;
				std::cout << "ERROR!";
				break;
			}
			else
				current = current->next;
		}
		else if (expectation.Level >= whileLevel){
			if (_condition->Count() == 0){
				CompileCondition* condition = new CompileCondition();
				_condition->add(new DoNothingNode());
				condition->Compile(cTokenList, *current, *current->previous->getPartner(), *_condition, *_condition->getLast());
				current = current->previous->getPartner();
			}
			else{
				bodyNode = _body->add(new DoNothingNode());
				while (current->getLevel() > whileLevel){
					Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(current->getEnum());
					if (compiledBodyPart != nullptr){
						compiledBodyPart->Compile(cTokenList, *current, *current->previous->getPartner(), *_body, *_body->getLast());
						current = current->previous->getPartner();
						begin = *current;
					}
					else
						current = current->next;
				}
			}
		}
	}

	ConnectLists();
	listActionNodes.add(_compiledStatement);
}


CompileElseIf::~CompileElseIf()
{
	delete _compiledStatement, _condition, _body;
}
