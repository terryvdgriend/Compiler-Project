#include "stdafx.h"
#include "CompileArray.h"

#include "ConditionalJumpNode.h"
#include "JumpGotoNode.h"
#include "DoNothingNode.h"
#include "CompileFactory.h"
#include "TokenExpectation.h"

CompileArray::CompileArray()
{
	_compiledArray = new LinkedActionList();
	_arrayBody = new LinkedActionList();
}

CompileArray::~CompileArray()
{
	delete _compiledArray, _arrayBody;
}

void CompileArray::connectList()
{
	_compiledArray->add(new DoNothingNode());
	_compiledArray->add(_arrayBody);
}

void CompileArray::Compile(LinkedList& cTokenList, Token& begin, Token& end, LinkedActionList& listActionNodes, ActionNode& actionBefore)
{
	Token* current = &begin;
	int arrayLevel = begin.getLevel();
	
	list<TokenExpectation> expected = list<TokenExpectation>();
	expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_OPEN));
	expected.push_back(TokenExpectation(arrayLevel, Token::NUMBER));
	expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_CLOSE));
	expected.push_back(TokenExpectation(arrayLevel, Token::IDENTIFIER));
	expected.push_back(TokenExpectation(arrayLevel, Token::EQUALS));
	expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_OPEN));
	expected.push_back(TokenExpectation(arrayLevel + 1, Token::ANY));
	expected.push_back(TokenExpectation(arrayLevel, Token::ARRAY_CLOSE));

	for (TokenExpectation expectation : expected)
	{
		while (current->getEnum() == Token::NEWLINE)
		{
			if (current->next != nullptr)
			{
				current = current->next;
			}
			else
			{
				break;
			}
		}

		if (expectation.Level == arrayLevel)
		{
			if (current == nullptr) {
				ErrorHandler::getInstance()->addError(Error{ "array making not completed", ".md",-1, -1, Error::error });
				begin = end;
				break;
			}
			if (current->getEnum() != expectation.TokenType) {
				ErrorHandler::getInstance()->addError(Error{ "", ".md", current->getLevel(), current->getPositie(), Error::error }, expectation.TokenType, current->getEnum());
				begin = end;
				break;
			}

			current = current->next;
		}
		else if (expectation.Level >= arrayLevel)
		{
			Token* prev = current->previous;
			while (prev->getEnum() != Token::ARRAY_OPEN)
			{
				prev = prev->previous;
			}
			prev = prev->getPartner();

			while (current->getLevel() > arrayLevel)
			{
				Compiler* compiledBodyPart = CompileFactory().CreateCompileStatement(*current);

				if (compiledBodyPart != nullptr)
				{
					compiledBodyPart->Compile(cTokenList, *current, *prev, *_arrayBody, *_arrayBody->getLast());
				}
				else
				{
					current = current->next;
				}
				delete compiledBodyPart;
			}
		}
	}

	connectList();
	listActionNodes.add(_compiledArray);
	begin = *current;
}