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
	_compiledStatement	= make_shared<LinkedActionList>();
	_condition			= make_shared<LinkedActionList>();
	_body				= make_shared<LinkedActionList>();
	_compiledStatement->add(new DoNothingNode());
}

void CompileElseIf::compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore){};
void CompileElseIf::compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore, map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>& _conditionBodyMap)
{
	//Check if all the tokens are correct
	Token* current = &begin;
	int whileLevel = begin.getLevel();
	list<TokenExpectation> expected = list<TokenExpectation>();
	expected.push_back(TokenExpectation(whileLevel, Token::ELIF));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::CONDITION_CLOSE));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_OPEN));
	expected.push_back(TokenExpectation(whileLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(whileLevel, Token::BODY_CLOSED));

	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE)
		{
			current = current->next;
		}

		if (expectation.getLevel() == whileLevel)
		{
			if (current == nullptr)
			{
				ErrorHandler::getInstance()->addError(Error{ "while statement not completed", ".md", -1, -1, Error::error });
				begin = end;

				break;
			}

			if (current->getEnum() != expectation.getTokenType())
			{
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.getTokenType(), current->getEnum());
				begin = end;

				break;
			}
			else
			{
				current = current->next;
			}
		}
		else if (expectation.getLevel() >= whileLevel)
		{
			if (_condition->Count() == 0)
			{
				CompileCondition* condition = new CompileCondition();
				_condition->add(new DoNothingNode());
				condition->Compile(cTokenList, *current, *current->previous->getPartner(), *_condition, *_condition->getLast());
				delete condition;
			}
			else
			{
				bodyNode = _body->add(new DoNothingNode());
				Token* prev = current->previous;

				while (prev->getEnum() != Token::BODY_OPEN)
				{
					prev = prev->previous;
				}
				prev = prev->getPartner();

				while (current->getLevel() > whileLevel)
				{
					Compiler* compiledBodyPart = CompileFactory().createCompileStatement(*current);

					if (compiledBodyPart != nullptr)
					{
						compiledBodyPart->compile(cTokenList, *current, *prev, *_body, *_body->getLast());
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
	_conditionBodyMap[_condition] = _body;
	//ConnectLists();
	//listActionNodes.add(_compiledStatement);
	begin = *current;
}

shared_ptr<Compiler> CompileElseIf::create()
{ 
	return make_shared<CompileElseIf>(); 
};

void CompileElseIf::connectLists() 
{
	ConditionalJumpNode* conditionalJumpNode = new ConditionalJumpNode();
	_compiledStatement->add(_condition);
	_compiledStatement->add(conditionalJumpNode);
	_compiledStatement->add(_body);
	_compiledStatement->add(new DoNothingNode());
	conditionalJumpNode->setOnTrue(_body->getFirst());
	conditionalJumpNode->setOnFalse(_compiledStatement->getLast());
}