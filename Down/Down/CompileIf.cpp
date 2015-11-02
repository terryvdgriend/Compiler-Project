#include "stdafx.h"
#include "CompileIf.h"
#include "CompileElseIf.h"
#include "CompileCondition.h"
#include "ConditionalJumpNode.h"
#include "JumpGotoNode.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"
#include "TokenExpectation.h"

CompileIf::CompileIf()
{
    _compiledStatement = new LinkedActionList();
    _condition = new LinkedActionList();
    _body = new LinkedActionList();
    _bodyElse = new LinkedActionList();
    _compiledStatement->add(new DoNothingNode());
}

void CompileIf::ConnectLists(){
    ConditionalJumpNode* conditionalJumpNode = new ConditionalJumpNode();
    _compiledStatement->add(_condition);
    _compiledStatement->add(conditionalJumpNode);
    _compiledStatement->add(_body);
    _compiledStatement->add(new DoNothingNode());
    conditionalJumpNode->setOnTrue(_body->getFirst());
    conditionalJumpNode->setOnFalse(_compiledStatement->getLast());
}

void CompileIf::ConnectListsWithElse(){
    ConditionalJumpNode* conditionalJumpNode = new ConditionalJumpNode();
	JumpGoToNode* jumpOverSecondBody = new JumpGoToNode();
    DoNothingNode* secondBodyStart = new DoNothingNode();
    _compiledStatement->add(_condition);
    _compiledStatement->add(conditionalJumpNode);
    _compiledStatement->add(_body);
    _compiledStatement->add(jumpOverSecondBody);
    _compiledStatement->add(secondBodyStart);
    _compiledStatement->add(_bodyElse);
    _compiledStatement->add(new DoNothingNode);
    jumpOverSecondBody->setJumpToNode(_compiledStatement->getLast());
    conditionalJumpNode->setOnTrue(_body->getFirst());
    conditionalJumpNode->setOnFalse(secondBodyStart);
}

void CompileIf::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	//Check if all the tokens are correct
	Token* current = &begin;
	int whileLevel = begin.getLevel();
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(whileLevel, Token::IF));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_CLOSE));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_CLOSED));

	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE){
			current = current->next;
		}
		if (expectation.Level == whileLevel){
			if (current == nullptr){
				ErrorHandler::getInstance()->addError(Error{ "if statement not completed", ".md",-1, -1, Error::error });
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
			if (_condition->Count() == 0){
				CompileCondition* condition = new CompileCondition();
				_condition->add(new DoNothingNode());
				condition->Compile(cTokenList, *current, *current->previous->getPartner(), *_condition, *_condition->getLast());
				delete condition;
			}
			else{
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
		}
	}
	if (current != nullptr){
		//Check if there is an else if-statement 
		while (current->getEnum() == Token::NEWLINE){
			current = current->next;
		}
		while (current->getEnum() == Token::ELIF)
		{
			CompileElseIf* compileElseIf = new CompileElseIf;
			compileElseIf->Compile(cTokenList, *current, end, *_body, *_body->getLast());
			if (current->next != nullptr){
				current = current->next;
			}
		}
		//Check if there is an else-statement 
		if (current->getEnum() == Token::ELSE)
		{
			int whileLevel = begin.getLevel();
			std::list<TokenExpectation> expected = std::list<TokenExpectation>();
			expected.push_back(TokenExpectation(whileLevel, Token::ELSE));
			expected.push_back(TokenExpectation(whileLevel, Token::BODY_OPEN));
			expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
			expected.push_back(TokenExpectation(whileLevel, Token::BODY_CLOSED));

			for (TokenExpectation expectation : expected)
				//for each (TokenExpectation expectation in expected)
			{
				while (current->getEnum() == Token::NEWLINE){
					current = current->next;
				}
				if (expectation.Level == whileLevel){
					if (current == nullptr){
						ErrorHandler::getInstance()->addError(Error{ "else statement not completed", ".md", -1, -1, Error::error });
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
					bodyNode = _bodyElse->add(new DoNothingNode());
					Token* prev = current->previous;
					while (prev->getEnum() != Token::BODY_OPEN){
						prev = prev->previous;
					}
					prev = prev->getPartner();
					while (current->getLevel() > whileLevel){
						Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(*current);

						if (compiledBodyPart != nullptr){
							compiledBodyPart->Compile(cTokenList, *current, *prev, *_bodyElse, *_bodyElse->getLast());
						}
						else
						{
							current = current->next;
						}
						delete compiledBodyPart;
					}
				}
			}
			//Build list with else
			ConnectListsWithElse();
		}
		else {
			//Build list without else
			ConnectLists();
		}

	}
	else {
		//Build list without else
		ConnectLists();
	}


	listActionNodes.add(_compiledStatement);
	begin = *current;
}


CompileIf::~CompileIf()
{
    delete _compiledStatement, _condition, _body, _bodyElse;
}
