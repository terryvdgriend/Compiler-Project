#include "stdafx.h"
#include "Tokenizer.h"
#include "Format.h"
#include "TokenMap.h"
#include "TokenRegex.h"

Tokenizer::Tokenizer()
{
	tokenMap		= TokenMap::getTokenMap();
	tokenRegex		= TokenRegex::getTokenRegex();
	currentScope	= 0;
	maxScope		= 0;
	tokenError		= false;
	actualRegex		= regex("(\\*{2}\\S+?\\*{2}|#+ (?:else if|\\w+)|and gives|multiplied by|(>.*)|(like or )?(\\w+) than|-?\\d+(?:\\.\\d+)?|\"(?:.*?)\"|\\w+|-{1,3}|[\\S|\\n])");
	//actualRegex = regex("(\\*{2}\\S+?\\*{2}|#+ (?:else if|\\w+)|and gives|multiplied by|(>.*)|(like or )?(\\w+) than|^-?\\d.?\\d*$|\"(.*?)\"|\\w+|-{1,3}|[\\S|\\n])");

}

void Tokenizer::createTokenList(shared_ptr<LinkedTokenList>& tokenList, const string codefromfile)
{
	shared_ptr<Token> token;
	string code = codefromfile;

	replace(code.begin(), code.end(), '\t', ' ');
	smatch match;
	int rowNr = 0;
	int colNr = 1;
	int lvl = 1;

	while (regex_search(code, match, actualRegex))
	{
		token = make_shared<Token>();
		IToken currentToken;
		string part = match[0];

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
            shared_ptr<Error> error = make_shared<Error>("Token not found &#9785; ", "unknown.MD", rowNr, colNr, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
		}

		if (tokenList->getLast() != nullptr && tokenList->getLast()->getType() == IToken::NEWLINE && currentToken == IToken::IDENTIFIER)
		{
			string lookahead = lookAhead(match);
			IToken lookaheadToken;

			if (tokenMap.find(lookahead) != tokenMap.end())
			{
				lookaheadToken = tokenMap[lookahead];
			}
			else
			{
				lookaheadToken = getToken(lookahead);
			}

			if (lookaheadToken == IToken::ARRAY_OPEN)
			{
				part.push_back(currentScope + '0');
				shared_ptr<Token> first = tokenList->getFirst();

				while (first->getNext() != nullptr)
				{
					if (first->getText() == part)
					{
						token->setSubType(first->getSubType());

						break;
					}
					first = first->getNext();
				}
			}
		}

		if ((tokenList->getLast() != nullptr && tokenList->getLast()->getType() == IToken::ARRAY_CLOSE) && currentToken == IToken::IDENTIFIER)
		{
			token->setSubType(tempToken);
			tempToken = IToken::NONE;
			part.push_back(currentScope + '0');

			if (tokenMap.count(part) != 0)
			{
                auto error = make_shared<Error>("identifier '" + part + "' is already defined", "unknown.MD", rowNr, colNr, ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error);
			}
			tokenMap[part] = IToken::IDENTIFIER;
			varTokenMap[part] = token->getSubType();
		}
		else if (currentToken == IToken::TYPE_NUMBER || currentToken == IToken::TYPE_TEXT || currentToken == IToken::TYPE_FACT)
		{
			lookAheadMethod(match, code, token, currentToken, part, rowNr, colNr, true);
		}
		else if (currentToken == IToken::NUMBER)
		{
			token->setSubType(IToken::TYPE_NUMBER);
		}
		else if (currentToken == IToken::TEXT) 
		{
			token->setSubType(IToken::TYPE_TEXT);
		}
		else if (currentToken == IToken::FACT) 
		{
			token->setSubType(IToken::TYPE_FACT);
		}
		else if (currentToken == IToken::FUNCTION_DECLARE)
		{
			auto it = tokenMap.find(part.substr(4, part.length() - 1));

            if (it != tokenMap.end())
			{
                auto error= make_shared<Error>("function '" + part + "' is already defined", "unknown.MD", rowNr, colNr, ErrorType::ERROR);
                ErrorHandler::getInstance()->addError(error);
            }
			else 
			{
				tokenMap[part.substr(4, part.length() - 1)] = IToken::FUNCTION_CALL;
				part = part.substr(4, part.length() - 1);
			}
		}
		else if (currentToken == IToken::FUNCTIONUSE)
		{
			if (tokenMap.count(part) != 0)
			{
				shared_ptr<Error> error = make_shared<Error>("function '" + part + "' is undefined", "unknown.MD", rowNr, colNr, ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error);
			}
		}
		else if (currentToken == IToken::IDENTIFIER)
		{
			if (token->getSubType() == IToken::NONE)
			{
				part.push_back(currentScope + '0');

				if (tokenMap.count(part) == 0)
				{
					shared_ptr<Error> error = make_shared<Error>("identifier '" + part + "' is undefined", "unknown.MD", rowNr, colNr, ErrorType::ERROR);
					ErrorHandler::getInstance()->addError(error);
				}
				map<string, IToken>::iterator it = varTokenMap.find(part);

				if (it != varTokenMap.end())
				{
					token->setSubType(it->second);
				}
			}
		}
		else if (currentToken == IToken::NEWLINE || currentToken == IToken::COMMENT) // New Lines
		{
			colNr = 1; 
			rowNr++;
		}
		token->setText((part));
		token->setLevel(lvl);
		token->setPosition(colNr);
		token->setPositionInList(tokenList->getSize());
		token->setLineNumber(rowNr);
		token->setType(currentToken);
		token->setPartner(nullptr);
		token->setScope(currentScope);

		// Add + Next
		if (currentToken != IToken::COMMENT)
		{
			tokenList->add(token);
		}

		// Levels
		if (currentToken == IToken::BODY_OPEN || currentToken == IToken::CONDITION_OPEN || currentToken == IToken::FUNCTION_OPEN || 
			currentToken == IToken::FUNCTION_DECLARE_OPEN || currentToken == IToken::ARRAY_OPEN)
		{
			if (currentToken == IToken::FUNCTION_OPEN) 
			{
				maxScope++;
				currentScope = maxScope;
			}
			lvl++;
		}

		// ++col
		colNr += part.size() + 1;

		// Levels
		if (currentToken == IToken::BODY_CLOSE || currentToken == IToken::CONDITION_CLOSE || currentToken == IToken::FUNCTION_CLOSE || 
			currentToken == IToken::FUNCTION_DECLARE_CLOSE || currentToken == IToken::ARRAY_CLOSE)
		{
			lvl--;
		}

		// Check remaining stack
		checkStack(token, lvl);
		code = match.suffix().str();

		if (currentToken == IToken::FUNCTION_CLOSE)
		{
			if (token->getPartner() == nullptr) 
			{
				shared_ptr<Error> error = make_shared<Error>("function body is not declared", "unknown.MD", rowNr, colNr, ErrorType::ERROR);
				ErrorHandler::getInstance()->addError(error);
			}
			else
			{
				currentScope = token->getPartner()->getScope();
			}
		}
	}
	checkRemainingStack();
	checkRemainingErrors();
}

void Tokenizer::printTokenList(shared_ptr<LinkedTokenList>& tokenList)
{
	Text::printLine("POSITIELIJST - REGELNR - POSITIE - TEXT - LEVEL - PARTNER");
	shared_ptr<Token> nextToken = tokenList->getFirst();

	while (nextToken != nullptr)
	{
		nextToken->print(tokenMap);
		nextToken = nextToken->getNext();
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
	auto customFunction = CommandDictionary::getCustomFunctions();
	int size = customFunction.size();

	for (auto cf : customFunction)
	{
		JSON += "{\"function\":\"" + cf->getName() + "\"}";

		if (i < size - 1)
		{
			JSON += ",";
		}
		i++;
	}
	JSON += "]";

	return JSON;
}

string Tokenizer::getKeyByValueTokenMap(IToken tokenType)
{
	for (map<string, IToken>::const_iterator it = tokenMap.begin(); it != tokenMap.end(); ++it)
	{
		if (it->second == tokenType)
		{
			return it->first;
		}
	}

	for (unordered_map<string, IToken>::iterator it = tokenRegex.begin(); it != tokenRegex.end(); ++it)
	{
		if (it->second == tokenType)
		{
			switch (it->second)
			{
				case IToken::NUMBER: 
				{
					return "number";
				}
				case IToken::TEXT:
				{
					return "text";
				}
				case IToken::FACT: 
				{
					return "fact";
				}
				default: 
				{
					return "";
				}
			}
		}
	}

	return "";
}

void Tokenizer::checkStack(shared_ptr<Token>& token, int& level)
{
	checkCondition(token);
	checkBrackets(token, level);
}

void Tokenizer::checkCondition(shared_ptr<Token>& token)
{
	if (token->getType() == IToken::DO)
	{
		stack.push(token);
	}
	else if (token->getType() == IToken::WHILE)
	{
		if (stack.size() > 0 && stack.top()->getType() == IToken::DO) 
		{
			shared_ptr<Token> stackToken = stack.top();
			token->setPartner(stackToken);
			stackToken->setPartner(token);
			stack.pop();
		}
	}
	else if (token->getType() == IToken::IF)
	{
		if (stack.size() > 0 && stack.top()->getType() == IToken::IF || stack.size() > 0 && stack.top()->getType() == IToken::ELSEIF)
		{
			stack.pop();
		}
		stack.push(token);
	}
	else if (token->getType() == IToken::ELSE)
	{
		if (stack.size() > 0 && stack.top()->getType() == IToken::IF)
		{
			shared_ptr<Token> stackToken = stack.top();
			token->setPartner(stackToken);
			stackToken->setPartner(token);
			stack.pop();
		}
		else if (stack.size() > 0 && stack.top()->getType() == IToken::ELSEIF)
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
	else if (token->getType() == IToken::ELSEIF)
	{
		if (stack.size() > 0 && stack.top()->getType() == IToken::IF)
		{
			shared_ptr<Token> stackToken = stack.top();
			token->setPartner(stackToken);
			stackToken->setPartner(token);
			stack.pop();
			stack.push(token);
		}
		else if (stack.size() > 0 && stack.top()->getType() == IToken::ELSEIF)
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

void Tokenizer::checkBrackets(shared_ptr<Token>& token, int& level)
{
	if (token->getType() == IToken::BODY_OPEN || token->getType() == IToken::CONDITION_OPEN || 
		token->getType() == IToken::FUNCTION_OPEN || token->getType() == IToken::ARRAY_OPEN || 
		token->getType() == IToken::FUNCTION_DECLARE_OPEN)
	{
		stack.push(token);
	}
	else if (token->getType() == IToken::BODY_CLOSE || token->getType() == IToken::CONDITION_CLOSE || 
			 token->getType() == IToken::FUNCTION_CLOSE || token->getType() == IToken::ARRAY_CLOSE || 
			 token->getType() == IToken::FUNCTION_DECLARE_CLOSE)
	{
		if (stack.size() > 0)
		{
			if ((token->getType() == IToken::BODY_CLOSE && stack.top()->getType() == IToken::IF) && token->getLevel() == stack.top()->getLevel()
				|| (token->getType() == IToken::BODY_CLOSE && stack.top()->getType() == IToken::ELSEIF) && token->getLevel() == stack.top()->getLevel())
			{
				if (stack.size() > 1) {
					auto topToken = stack.top();
					stack.pop();
					if (stack.top()->getType() == IToken::BODY_OPEN && stack.top()->getLevel() == token->getLevel()) {
						stack.push(topToken);
					}
				}
				else if (token->getNext() != nullptr)
				{
					if (token->getNext()->getType() != IToken::ELSE)
					{
						stack.pop();
					}
				}
			}
			else if ((token->getType() == IToken::FUNCTION_CLOSE && stack.top()->getType() == IToken::IF || token->getType() == IToken::FUNCTION_CLOSE && stack.top()->getType() == IToken::ELSEIF) && token->getLevel() == stack.top()->getLevel()) {
				stack.pop();
			}

			if ((token->getType() == IToken::BODY_CLOSE && stack.top()->getType() == IToken::BODY_OPEN) ||
				(token->getType() == IToken::FUNCTION_CLOSE && stack.top()->getType() == IToken::FUNCTION_OPEN) ||
				(token->getType() == IToken::FUNCTION_DECLARE_CLOSE && stack.top()->getType() == IToken::FUNCTION_DECLARE_OPEN) ||
				(token->getType() == IToken::ARRAY_CLOSE && stack.top()->getType() == IToken::ARRAY_OPEN) ||
				(token->getType() == IToken::CONDITION_CLOSE && stack.top()->getType() == IToken::CONDITION_OPEN))
			{
				token->setLevel(level);
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
	while (stack.size() > 0 && (stack.top()->getType() == IToken::IF || stack.top()->getType() == IToken::ELSEIF))
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

string Tokenizer::lookAhead(smatch match)
{
	smatch _match;
	string lookaheadResult = match.suffix().str();
	regex_search(lookaheadResult, _match, actualRegex);

	return _match[0];
}

void Tokenizer::lookAheadMethod(smatch& match, string& codePart, shared_ptr<Token>& token, IToken& currentToken, string& part, int rowNr, int colNr, bool arrayOpen)
{
	string lookaheadResult = lookAhead(match);
	IToken lookaheadToken;

	if (tokenMap.find(lookaheadResult) != tokenMap.end())
	{
		lookaheadToken = tokenMap[lookaheadResult];
	}
	else
	{
		lookaheadToken = getToken(lookaheadResult);
	}

	if (lookaheadToken == IToken::IDENTIFIER)
	{
		lookaheadResult.push_back(currentScope + '0');

		if (tokenMap.count(lookaheadResult) != 0)
		{
            auto error = make_shared<Error>("identifier '" + lookaheadResult + "' is already defined", "unknown.MD", rowNr, colNr, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
		}
		token->setSubType(currentToken);
		currentToken = lookaheadToken;

		tokenMap[lookaheadResult] = IToken::IDENTIFIER;
		part = lookaheadResult;
		codePart = match.suffix().str();
		regex_search(codePart, match, actualRegex);
		varTokenMap[part] = token->getSubType();
	}
	else if (lookaheadToken == IToken::ARRAY_OPEN)
	{
		switch (currentToken)
		{
			case IToken::TYPE_NUMBER:
			{
				tempToken = IToken::TYPE_NUMBER_ARRAY;

				break;
			}
			case IToken::TYPE_TEXT:
			{
				tempToken = IToken::TYPE_TEXT_ARRAY;

				break;
			}
			case IToken::TYPE_FACT:
			{
				tempToken = IToken::TYPE_FACT_ARRAY;

				break;
			}
		}
		currentToken = lookaheadToken;
		part = lookaheadResult;
		codePart = match.suffix().str();
		regex_search(codePart, match, actualRegex);
	}
	else
	{
		if (arrayOpen)
		{
            auto error = make_shared<Error>("Expected an identifier", "unknown.MD", rowNr, colNr, ErrorType::ERROR);
			ErrorHandler::getInstance()->addError(error);
		}
	}
}

IToken Tokenizer::getToken(string token)
{
	smatch match;

	for (unordered_map<string, IToken>::iterator it = tokenRegex.begin(); it != tokenRegex.end(); it++)
	{
		regex e(it->first);
		regex_search(token, match, e);

		if (match.size() != 0)
		{
			return it->second;
		}
	}

	return IToken::NONE;
}

IToken Tokenizer::getNextToken(smatch& match, string& codePart)
{
	string lookaheadResult = lookAhead(match);
	IToken lookaheadToken;

	if (tokenMap.find(lookaheadResult) != tokenMap.end())
	{
		lookaheadToken = tokenMap[lookaheadResult];
	}
	else
	{
		lookaheadToken = getToken(lookaheadResult);
	}

	return lookaheadToken;
}