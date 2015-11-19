#include "stdafx.h"
#include "CompileUserFunction.h"

#include "CompileCondition.h"

CompileUserFunction::CompileUserFunction() 
{
	_compiledStatement = new LinkedActionList();
	//_condition = new LinkedActionList();
	//_body = new LinkedActionList();
	_compiledStatement->add(new DoNothingNode());
}

void CompileUserFunction::Compile(LinkedList & cTokenList, Token & begin, Token & end, LinkedActionList & listActionNodes, ActionNode & actionBefore)
{
	//begin = *begin.getPartner();
	Token* current = &begin;
	int Level = begin.getLevel();
	//
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(Level, Token::FUNCTION_OPEN));
	expected.push_back(TokenExpectation(Level, Token::FUNCTION));
	expected.push_back(TokenExpectation(Level + 1, Token::COMINGPARAMETER));
	expected.push_back(TokenExpectation(Level, Token::CONDITION_CLOSE));
	expected.push_back(TokenExpectation(Level, Token::BODY_OPEN));
	expected.push_back(TokenExpectation(Level + 1, Token::ANY));
	expected.push_back(TokenExpectation(Level, Token::FUNCTION_CLOSE));
	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE) {
			current = current->next;
		}
		if (current->getEnum() != expectation.TokenType) {
			ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, current->getEnum());
			begin = end;
			break;
		}
		else
			current = current->next;
	}
}

CompileUserFunction::~CompileUserFunction()
{
}
