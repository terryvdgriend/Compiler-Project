#include "stdafx.h"
#include "CompileUserFunction.h"
#include "CompileFactory.h"
#include "CompileCondition.h"

CompileUserFunction::CompileUserFunction() 
{
	_body = new LinkedList();
	_returnToken = nullptr;
}

void CompileUserFunction::ConnectList() {
	Function func = Function(functionName,_params,_body,_paramTokens,_returnToken,true);
	FunctionHandler::getInstance()->addFunction(func);
}

void CompileUserFunction::Compile(LinkedList & cTokenList, Token & begin, Token & end, LinkedActionList & listActionNodes, ActionNode & actionBefore)
{
	Token* current = &begin;
	int Level = begin.getLevel();

	Token* bodyEnd = nullptr;
	//
	std::list<TokenExpectation> expected = std::list<TokenExpectation>();
	expected.push_back(TokenExpectation(Level, Token::FUNCTION_OPEN));
	expected.push_back(TokenExpectation(Level, Token::FUNCTION_DECLARE));
	expected.push_back(TokenExpectation(Level + 1, Token::ANY));
	expected.push_back(TokenExpectation(Level, Token::FUNCTION_CLOSE));
	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE) {
			current = current->next;
		}
		if (expectation.getLevel() == Level) {
			if (current->getEnum() == Token::FUNCTION_OPEN) {
				bodyEnd = current->getPartner();
			}
			else if (current->getEnum() == Token::FUNCTION_DECLARE) {
				functionName = current->getText();
			}
			if (current->getEnum() != expectation.getTokenType()) {
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.getTokenType(), current->getEnum());
				begin = end;
				break;
			}
			else
				current = current->next;
		}
		else {
			//check if enum is comingparam else body;
			if (current->getEnum() == Token::START_PARAMETERS) {
				CompileParams(cTokenList,* current, end);
				CompileBody(cTokenList, *current, *bodyEnd,Level);
			}
			else
			{
				CompileBody(cTokenList, *current, *bodyEnd,Level);
			}
		}
	}
	ConnectList();
	begin = *current;
}
void CompileUserFunction::CompileParams(LinkedList & cTokenList, Token & begin, Token & end)
{
	Token* current = &begin;
	
	while (current->getEnum() != Token::NEWLINE)
	{
		if (current->getText() == functionName) {
			ErrorHandler::getInstance()->addError(Error{ functionName + " Cannot call itself", ".md", current->getLineNumber(),current->getPositie(), Error::error });
			current = &end;
			break;
		}
		if (current->getEnum() == Token::IDENTIFIER)
		{
			if (current->previous != nullptr && current->previous->getEnum() == Token::RETURNVALUE) {
				_returnToken = new Token(*current);
			}
			else {
				switch (current->getSub()) {
					case Token::TYPE_NUMBER: {
						_params += 'i';
						break;
					}
					case Token::TYPE_FACT: {
						_params += 'b';
						break;
					}
					case Token::TYPE_TEXT: {
						_params += 's';
						break;
					}
					default: {
						_params += 'a';
						break;
					}
				}
				_paramTokens.push_back(new Token(*current));
			}
			
		}
			
		current = current->next;
	}

	begin = *current;
}

void CompileUserFunction::CompileBody(LinkedList & cTokenList, Token & begin, Token & end,int Level)
{
	Token* current = &(begin);

	do {
		if (current->getText() == functionName) {
			ErrorHandler::getInstance()->addError(Error{ functionName + " Cannot call itself", ".md", current->getLineNumber(),current->getPositie(), Error::error });
			current = &end;
			break;
		}
		_body->add(new Token(*current));
		current = current->next;
	} while (current->getEnum() != end.getEnum());
	begin = *current;
}

CompileUserFunction::~CompileUserFunction()
{
}
