#include "stdafx.h"
#include "Tokenizer.h"
#include "Format.h"
#include "LinkedList.h"
#include "TokenMap.h"
#include "TokenRegex.h"

Tokenizer::Tokenizer()
{
	tokenMap		= TokenMap::getTokenMap();
	tokenRegex		= TokenRegex::getTokenRegex();
	currentScope	= 0;
	maxScope		= 0;
	tokenError		= false;
	actualRegex		= regex("(#+ (?:else if|else|if|case|while|do|foreach|for|\\w+)|and gives|multiplied by|(^>.*\\n)|(smaller|larger) than|^-?\\d.?\\d*$|\"(.*?)\"|\\w+|\\*\\*\\S*?\\*\\*|-{1,3}|^[\\(\\)\\[\\]]$|[\\S|\\n])");
}

void Tokenizer::createTokenList(shared_ptr<LinkedList>& tokenList, string codefromfile)
{
	shared_ptr<Token> pToken;
	string s = codefromfile;
	smatch m;
	int rowNr = 1;
	int colNr = 1;
	int lvl = 1;

	while (regex_search(s, m, actualRegex))
	{
		pToken = make_shared<Token>();
		IToken currentToken;
		string part = m[0];

		if (tokenMap.find(part) != tokenMap.end())
		{
			currentToken = tokenMap[part];
		}
		else
		{
			currentToken = getToken(part);
		}
		// No token found, so add error
		if (currentToken == IToken::NONE)
		{
			ErrorHandler::getInstance()->addError(make_shared<Error>("Token not found &#9785; ", "unknown.MD", rowNr, colNr, ErrorType::error));
		}

		if (currentToken == IToken::TYPE_NUMBER || currentToken == IToken::TYPE_TEXT || currentToken == IToken::TYPE_FACT)
		{
			string lookahead = lookAhead(m, s);
			IToken lookaheadToken;

			if (tokenMap.find(lookahead) != tokenMap.end())
			{
				lookaheadToken = tokenMap[lookahead];
			}
			else
			{
				lookaheadToken = getToken(lookahead);
			}

			if (lookaheadToken == IToken::IDENTIFIER)
			{
				lookahead.push_back(currentScope + '0');

				if (tokenMap.count(lookahead) != 0)
				{
					ErrorHandler::getInstance()->addError(make_shared<Error>("identifier '" + lookahead + "' is already defined", "unknown.MD", rowNr, colNr, ErrorType::error));
				}
				pToken->setSubType(currentToken);
				currentToken = lookaheadToken;

				tokenMap[lookahead] = IToken::IDENTIFIER;
				part = lookahead;
				s = m.suffix().str();
				regex_search(s, m, actualRegex);
			}
			else
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("Expected an identifier", "unknown.MD", rowNr, colNr, ErrorType::error));
			}
		}
		else if (currentToken == IToken::NUMBER)
		{
			pToken->setSubType(IToken::TYPE_NUMBER);
		}
		else if (currentToken == IToken::TEXT)
		{
			pToken->setSubType(IToken::TYPE_TEXT);
		}
		else if (currentToken == IToken::FACT)
		{
			pToken->setSubType(IToken::TYPE_FACT);
		}
		else if (currentToken == IToken::FUNCTION_DECLARE)
		{
			tokenMap[part.substr(4, part.length() - 1)] = IToken::FUNCTION_CALL;
			part = part.substr(4, part.length() - 1);
		}
		else if (currentToken == IToken::FUNCTIONUSE)
		{
			if (tokenMap.count(part) != 0)
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("function '" + part + "' is undefined", "unknown.MD", rowNr, colNr, ErrorType::error));
			}
		}
		else if (currentToken == IToken::IDENTIFIER)
		{
			part.push_back(currentScope + '0');

			if (tokenMap.count(part) == 0)
			{
				ErrorHandler::getInstance()->addError(make_shared<Error>("identifier '" + part + "' is undefined", "unknown.MD", rowNr, colNr, ErrorType::error));
			}
		}
		else if (currentToken == IToken::NEWLINE || currentToken == IToken::COMMENT) // New Lines
		{
			colNr = 1; rowNr++;
		}
		pToken->setText((part));
		pToken->setLevel(lvl);
		pToken->setPosition(colNr);
		pToken->setPositionInList(tokenList->getSize());
		pToken->setLineNumber(rowNr);
		pToken->setType(currentToken);
		pToken->setPartner(nullptr);
		pToken->setScope(currentScope);

		// Add + Next
		if (currentToken != IToken::COMMENT)
		{
			tokenList->add(pToken);
		}

		// Levels
		if (currentToken == IToken::BODY_OPEN || currentToken == IToken::CONDITION_OPEN ||
			currentToken == IToken::FUNCTION_OPEN || currentToken == IToken::FUNCTION_DECLARE_OPEN)
		{
			if (currentToken == IToken::FUNCTION_OPEN)
			{
				maxScope++;
				currentScope = maxScope;
			}
			lvl++;
		}

		// ++ col
		colNr += part.size() + 1;

		////Levels
		if (currentToken == IToken::BODY_CLOSED || currentToken == IToken::CONDITION_CLOSE ||
			currentToken == IToken::FUNCTION_CLOSE || currentToken == IToken::FUNCTION_DECLARE_CLOSE)
		{
			lvl--;
		}
		// Check remaining stack
		checkStack(pToken, lvl);

		if (tokenList->getLast()->getType() == IToken::BODY_CLOSED)
		{
			if (stack.size() > 0)
			{
				if ((stack.top()->getType() == IToken::IF || stack.top()->getType() == IToken::ELIF) && currentToken != IToken::ELIF)
				{
					checkRemainingStack();
				}
			}
		}
		s = m.suffix().str();

		if (currentToken == IToken::FUNCTION_CLOSE)
		{
			currentScope = pToken->getPartner()->getScope();
		}
	}
	checkRemainingStack();
	checkRemainingErrors();
}

void Tokenizer::printTokenList(shared_ptr<LinkedList>& tokenList)
{
	Text::printLine("POSITIELIJST - REGELNR - POSITIE - TEXT - LEVEL - PARTNER");
	shared_ptr<Token> start = tokenList->getFirst();

	while (start != nullptr) 
	{
		start->print(tokenMap);
		start = start->getNext();
	}
}

bool Tokenizer::getTokenError()
{
	return tokenError;
}

string Tokenizer::getKeywordsAsJson()
{
	string JSON = "[";
	int size = (int)tokenMap.size();
	int i = 0;

	for (map<string, IToken>::iterator it = tokenMap.begin(); it != tokenMap.end(); ++it)
	{
		if (it->second == IToken::NEWLINE)
		{
			i++;

			continue;
		}
		JSON += "{\"keyword\":\"" + it->first + "\"}";

		if (i < size - 1)
		{
			JSON += ",";
		}
		i++;
	}
	JSON += "]";

	return JSON;
}

string Tokenizer::getFunctionsAsJson()
{
	string JSON = "[";
	int i = 0;
	int size = CommandDictionary::getCustomFunctions().size();

	for (pair<string, shared_ptr<BaseCommand>> cf : CommandDictionary::getCustomFunctions())
	{
		JSON += "{\"function\":\"" + cf.first + "\"}";

		if (i < size - 1)
		{
			JSON += ",";
		}
		i++;
	}
	JSON += "]";

	return JSON;
}

string Tokenizer::getKeyByValueTokenMap(IToken type)
{
	for (map<string, IToken>::const_iterator it = tokenMap.begin(); it != tokenMap.end(); ++it)
	{
		if (it->second == type)
		{
			return it->first;
		}
	}

	return "";
}

void Tokenizer::checkStack(shared_ptr<Token>& token, int &lvl)
{
	checkCondition(token, lvl);
	checkBrackets(token, lvl);
}

void Tokenizer::checkCondition(shared_ptr<Token>& token, int &lvl)
{
	if (token->getType() == IToken::DO)
	{
		stack.push(token);
	}

	if (token->getType() == IToken::WHILE)
	{
		if (stack.size() > 0 && stack.top()->getType() == IToken::DO)
		{
			shared_ptr<Token> stackToken = stack.top();
			token->setPartner(stackToken);
			stackToken->setPartner(token);
			stack.pop();
		}
	}

	if (token->getType() == IToken::IF)
	{
		if (stack.size() > 0 && stack.top()->getType() == IToken::IF)
		{
			stack.pop();
		}
		stack.push(token);
	}

	if (token->getType() == IToken::ELSE)
	{
		if (stack.size() > 0 && stack.top()->getType() == IToken::IF)
		{
			shared_ptr<Token> stackToken = stack.top();
			token->setPartner(stackToken);
			stackToken->setPartner(token);
			stack.pop();
		}
		else if (stack.size() > 0 && stack.top()->getType() == IToken::ELIF)
		{
			shared_ptr<Token> stackToken = stack.top();
			shared_ptr<Token> partner = stackToken->getPartner();

			if (partner == nullptr)
			{
				stack.push(token);
			}
			else
			{
				while (partner->getType() != IToken::IF)
				{
					partner = partner->getPartner();
				}
				token->setPartner(partner);
				stackToken->setPartner(token);
				stack.pop();
			}
		}
		else
		{
			stack.push(token);
		}
	}

	if (token->getType() == IToken::ELIF)
	{
		if (stack.size() > 0 && stack.top()->getType() == IToken::IF)
		{
			shared_ptr<Token> stackToken = stack.top();
			token->setPartner(stackToken);
			stackToken->setPartner(token);
			stack.pop();
			stack.push(token);
		}
		else if (stack.size() > 0 && stack.top()->getType() == IToken::ELIF)
		{
			shared_ptr<Token> stackToken = stack.top();
			shared_ptr<Token> partner = stackToken->getPartner();

			if (partner != nullptr)
			{
				while (partner->getType() != IToken::IF)
				{
					partner = partner->getPartner();
				}
				token->setPartner(partner);
				stackToken->setPartner(token);
				stack.pop();
			}
			stack.push(token);
		}
		else
		{
			stack.push(token);
		}
	}
}

void Tokenizer::checkBrackets(shared_ptr<Token>& token, int &lvl)
{
	if (token->getType() == IToken::BODY_OPEN || token->getType() == IToken::CONDITION_OPEN || token->getType() == IToken::FUNCTION_OPEN ||
		token->getType() == IToken::ARRAY_OPEN || token->getType() == IToken::FUNCTION_DECLARE_OPEN)
	{
		stack.push(token);
	}
	else if (token->getType() == IToken::BODY_CLOSED || token->getType() == IToken::CONDITION_CLOSE || token->getType() == IToken::FUNCTION_CLOSE ||
		token->getType() == IToken::ARRAY_CLOSE || token->getType() == IToken::FUNCTION_DECLARE_CLOSE)
	{
		if (stack.size() > 0)
		{
			if ((token->getType() == IToken::BODY_CLOSED && stack.top()->getType() == IToken::IF) && token->getLevel() == stack.top()->getLevel())
			{
				if (token->getNext() != nullptr)
				{
					if (token->getNext()->getType() != IToken::ELSE)
					{
						stack.pop();
					}
				}
			}

			if ((token->getType() == IToken::BODY_CLOSED && stack.top()->getType() == IToken::BODY_OPEN) ||
				(token->getType() == IToken::FUNCTION_CLOSE && stack.top()->getType() == IToken::FUNCTION_OPEN) ||
				(token->getType() == IToken::FUNCTION_DECLARE_CLOSE && stack.top()->getType() == IToken::FUNCTION_DECLARE_OPEN) ||
				(token->getType() == IToken::ARRAY_CLOSE && stack.top()->getType() == IToken::ARRAY_OPEN) ||
				(token->getType() == IToken::CONDITION_CLOSE && stack.top()->getType() == IToken::CONDITION_OPEN))
			{
				token->setLevel(lvl);
				shared_ptr<Token> stackToken = stack.top();
				token->setPartner(stackToken);
				stackToken->setPartner(token);
				stack.pop();
			}
		}
	}
}

void Tokenizer::checkRemainingStack()
{
	if (stack.size() > 0 && (stack.top()->getType() == IToken::IF || stack.top()->getType() == IToken::ELIF))
	{
		stack.pop();
	}
}

void Tokenizer::checkRemainingErrors()
{
	if (stack.size() > 0)
	{
		tokenError = true;

		while (stack.size() > 0)
		{
			shared_ptr<Token> token = stack.top();
			stack.pop();
			token->addError();
		}
	}
}

string Tokenizer::lookAhead(smatch m, string s)
{
	smatch m2;
	string lookahead = m.suffix().str();
	regex_search(lookahead, m2, actualRegex);

	return m2[0];
}

IToken Tokenizer::getToken(string token)
{
	smatch m;
	typedef map<string, IToken>::iterator it_type;

	for (it_type iterator = tokenRegex.begin(); iterator != tokenRegex.end(); iterator++)
	{
		regex e(iterator->first);
		regex_search(token, m, e);

		if (m.size() != 0)
		{
			return iterator->second;
		}
	}

	return IToken::NONE;
}