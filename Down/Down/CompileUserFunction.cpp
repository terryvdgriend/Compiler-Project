#include "stdafx.h"
#include "CompileUserFunction.h"
#include "CompileFactory.h"
#include "CompileCondition.h"

CompileUserFunction::CompileUserFunction() 
{
	_compiledStatement = new LinkedActionList();
	//_condition = new LinkedActionList();
	_body = new LinkedActionList();
	_compiledStatement->add(new DoNothingNode());
}

void CompileUserFunction::Compile(LinkedList & cTokenList, Token & begin, Token & end, LinkedActionList & listActionNodes, ActionNode & actionBefore)
{
	//begin = *begin.getPartner();
	Token* current = &begin;
	int Level = begin.getLevel();

	Token* bodyEnd = nullptr;
	//
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(Level, Token::FUNCTION_OPEN));
	expected.push_back(TokenExpectation(Level, Token::FUNCTION));
	expected.push_back(TokenExpectation(Level + 1, Token::ANY));
	expected.push_back(TokenExpectation(Level, Token::FUNCTION_CLOSE));
	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE) {
			current = current->next;
		}
		if (expectation.Level == Level) {
			if (current->getEnum() == Token::FUNCTION_OPEN) {
				bodyEnd = current->getPartner();
			}
			if (current->getEnum() != expectation.TokenType) {
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, current->getEnum());
				begin = end;
				break;
			}
			else
				current = current->next;
		}
		else {
			//check if enum is comingparam else body;
			if (current->getEnum() == Token::COMINGPARAMETER) {
				CompileParams(cTokenList,* current, end);
				CompileBody(cTokenList, *current, *bodyEnd,Level);
			}
			else
			{
				CompileBody(cTokenList, *current, *bodyEnd,Level);
			}
		}
	}
	begin = *current;
}
void CompileUserFunction::CompileParams(LinkedList & cTokenList, Token & begin, Token & end)
{
	Token* current = &begin;


	//do dingen


	begin = *current;
}

void CompileUserFunction::CompileBody(LinkedList & cTokenList, Token & begin, Token & end,int Level)
{
	Token* current = &begin;

	while (current->getLevel() > Level) {
		Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(*current);

		if (compiledBodyPart != nullptr) {
			compiledBodyPart->Compile(cTokenList, *current, end, *_body, *_body->getLast());
		}
		else
		{
			current = current->next;
		}
		delete compiledBodyPart;
	}


	begin = *current;
}

CompileUserFunction::~CompileUserFunction()
{
}
