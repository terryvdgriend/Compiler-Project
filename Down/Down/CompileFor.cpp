#include "stdafx.h"
#include "CompileFor.h"
#include "CompileCondition.h"
#include "ConditionalJumpNode.h"
#include "JumpGoToNode.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"
#include "TokenExpectation.h"
#include "CompilePlusMinus.h"

CompileFor::CompileFor()
{
	_compiledStatement = new LinkedActionList();
	_declaration = new LinkedActionList();
	_increment = new LinkedActionList();
	_condition = new LinkedActionList();
	_body = new LinkedActionList();
	_compiledStatement->add(new DoNothingNode());
}

void CompileFor::ConnectLists(){
	ConditionalJumpNode* conditionalJumpNode = new ConditionalJumpNode();
	JumpGoToNode* jumpBackNode = new JumpGoToNode();
	_compiledStatement->add(_declaration);
	_compiledStatement->add(_condition);
	_compiledStatement->add(conditionalJumpNode);
	_compiledStatement->add(_body);
	_compiledStatement->add(_increment);
	_compiledStatement->add(jumpBackNode);
	_compiledStatement->add(new DoNothingNode());
	jumpBackNode->setJumpToNode(_condition->getFirst());
	conditionalJumpNode->setOnTrue(_body->getFirst());
	conditionalJumpNode->setOnFalse(_compiledStatement->getLast());
}

void CompileFor::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	Token* current = &begin;
	int whileLevel = begin.getLevel();
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(whileLevel, Token::FOR));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::AND_PARA));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::AND_PARA));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_CLOSE));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_CLOSED));
	Token* conClose = nullptr;
	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE){
			current = current->next;
		}
		if (expectation.Level == whileLevel){
			if (current == nullptr){
				ErrorHandler::getInstance()->addError(Error{ "for statement not completed", ".md", -1, -1, Error::error });
				begin = end;
				break;
			}
			if (current->getEnum() == Token::CONDITION_OPEN)
				conClose = current->getPartner();
			if (current->getEnum() != expectation.TokenType){
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, current->getEnum());
				begin = end;
				break;
			}
			else
				current = current->next;
		}
		else if (expectation.Level >= whileLevel){
			if (current->getEnum() == expectation.TokenType && current->getEnum() == Token::AND_PARA) {
				current = current->next;
				continue;
			}
			if (_declaration->Count() == 0){
				Token* next = current->previous;
				while (next->getEnum() != Token::AND_PARA){
					next = next->next;
				}

				// This means the declaration is empty
				if (next->previous->getEnum() == Token::CONDITION_OPEN)
				{
					ErrorHandler::getInstance()->addError(Error{ "For statement has no declaration!", ".md", current->getLineNumber(), current->getPositie(), Error::error });
					begin = end;
					return;
				}
				else {
					// Compile the first part of the for-loop

					Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(*current);

					if (compiledBodyPart != nullptr) {
						compiledBodyPart->Compile(cTokenList, *current, *next, *_declaration, *_declaration->getLast());

						// If the list still is empty, fill with DoNothingNode 
						if (_declaration->Count() == 0)
							_declaration->insertLast(new DoNothingNode());
					}
					else
					{
						current = current->next;
					}
					delete compiledBodyPart;
				}
			}
			else if (_condition->Count() == 0){
				Token* next = current->next;
				while (next->getEnum() != Token::AND_PARA) {
					next = next->next;
				}

				CompileCondition* condition = new CompileCondition();
				_condition->add(new DoNothingNode());
				condition->Compile(cTokenList, *current, *next, *_condition, *_condition->getLast());
				delete condition;

				// If condition still is empty, throw error (we need a condition)
				if (_condition->Count() == 0) {
					ErrorHandler::getInstance()->addError(Error{ "For statement has no condition!", ".md", current->getLineNumber(), current->getPositie(), Error::error });
					begin = end;
					break;
				}
			}
			else if (_increment->Count() == 0){
				// Compile the last part of the for-loop
				// TODO: Compile increment
				if (current->getEnum() == Token::CONDITION_CLOSE) {
					ErrorHandler::getInstance()->addError(Error{ "For statement has no increment!", ".md", current->getLineNumber(), current->getPositie(), Error::error });
					begin = end;
					return;
				}
				Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(*current);

				if (compiledBodyPart != nullptr){
					compiledBodyPart->Compile(cTokenList, *current, *conClose, *_increment, *_increment->getLast());
				}
				else
				{
					current = current->next;
				}
				delete compiledBodyPart;

			}
			else{
				Token* prev = current->previous;
				while (prev->getEnum() != Token::BODY_OPEN) {
					prev = prev->previous;
				}
				prev = prev->getPartner();
				_body->add(new DoNothingNode());
				while (current->getLevel() > whileLevel) {
					Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(*current);

					if (compiledBodyPart != nullptr) {
						compiledBodyPart->Compile(cTokenList, *current, *prev, *_body, *_body->getLast());
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
	ConnectLists();
	listActionNodes.insertBefore(&actionBefore, _compiledStatement)
	begin = *current;
}

CompileFor::~CompileFor()
{
	delete bodyNode;
	delete _body;
	delete _condition;
	delete _compiledStatement;
}
