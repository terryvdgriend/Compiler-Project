#include "stdafx.h"
#include "CompileGetFunction.h"


CompileGetFunction::CompileGetFunction()
{
	_body = new LinkedActionList();
	_compiledStatement = new LinkedActionList();
	_compiledStatement->add(new DoNothingNode());
}

void CompileGetFunction::ConnectLists()
{
	_compiledStatement->add(_body);
}

void CompileGetFunction::Compile(LinkedList & cTokenList, Token & begin, Token & end, LinkedActionList & listActionNodes, ActionNode & actionBefore)
{
	Token* current = &begin;
	int Level = begin.getLevel();

	Token* bodyEnd = nullptr;
	//
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(Level, Token::FUNCTION_DECLARE_OPEN));
	expected.push_back(TokenExpectation(Level, Token::FUNCTION_CALL));
	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE) {
			current = current->next;
		}
		if (expectation.getLevel() == Level) {
			if (current->getEnum() == Token::FUNCTION_CALL) {
				for (auto p : FunctionHandler::getInstance()->getFunctions()) 
				{
					if (!p.isUserdef())
					{
						Text::Print("WHOLLA");
					}
					if (p.getName() == current->getText()) {
						_params = p.getParams();
						_body = p.getBody();
						break;
					}
				}
			}
			if (current->getEnum() != expectation.getTokenType()) {
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.getTokenType(), current->getEnum());
				begin = end;
				break;
			}
			else
				current = current->next;
		}
	}
	if (current->getEnum() != Token::FUNCTION_DECLARE_CLOSE)
		CompileParams(cTokenList, *current, end);

	ConnectLists();
	begin = *current;
	listActionNodes.add(_compiledStatement);
}

void CompileGetFunction::CompileParams(LinkedList & cTokenList, Token & begin, Token & end)
{
	// dingen;
}

CompileGetFunction::~CompileGetFunction()
{
}
