#include "stdafx.h"
#include "CompileWhile.h"
#include "CompileCondition.h"
#include "ConditionalJumpNode.h"
#include "JumpGotoNode.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"
#include "TokenExpectation.h"

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
	Token* current = &begin;
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

			if (current == nullptr || current->getEnum() != expectation.TokenType){
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType,current->getEnum());
				begin = end;
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
				delete condition;
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
					{
						ErrorHandler::getInstance()->addError("Incorrect syntax ", current);
						current = current->next;
					}
					delete compiledBodyPart;
				}
			}
		}
	}
	ConnectLists();
	listActionNodes.add(_compiledStatement);
}

CompileWhile::~CompileWhile()
{
	delete bodyNode;
	delete _body;
	delete _condition;
	delete _compiledStatement;
}
