#include "stdafx.h"
#include "Tokenizer.h"
//
#include "Format.h"
#include "LinkedList.h"
#include "Tokenmap.h"
#include "Tokenregex.h"
//


Tokenizer::Tokenizer()
{
	mappert =  TokenMap::tm;
	regexert = TokenRegex::tr;
}

std::string Tokenizer::getKeyByValueMappert(Token::iToken tkn)
{
	for (std::map<std::string, Token::iToken>::const_iterator it = mappert.begin(); it != mappert.end(); ++it)
	{
		if (it->second == tkn)
			return it->first;
	}

	return "";
}

void Tokenizer::createTokenList(LinkedList& cTokenList, string codefromfile)
{
	//
	Token  *pToken{};
	string s(codefromfile);
	smatch m;

	int rowNr = 1;
	int colNr = 1;
	int lvl = 1;
	bool isFunctionCall = false;


	while (regex_search(s, m, e))
	{
		pToken = new Token;
		Token::iToken currentToken;
		string part = m[0];
		//currentToken = getToken(part);
		currentToken = (this->mappert.find(part) != mappert.end()) ? mappert[part] : getToken(part);

		// Geen token, dus add error
		if (currentToken == Token::NONE)
			ErrorHandler::getInstance()->addError(Error{ "Token not found &#9785;", "unknown.MD", rowNr, colNr, Error::errorType::error });

		if (isFunctionCall){
			currentToken = Token::FUNCTIONUSE;
			isFunctionCall = false;
		}

		if (currentToken == Token::FUNCTION_DECLARE_OPEN)
			isFunctionCall = true;
		else if (currentToken == Token::TYPE_NUMBER || currentToken == Token::TYPE_TEXT || currentToken == Token::TYPE_FACT)
		{
			std::string lookahead = lookAhead(m, s);
			Token::iToken lookaheadToken = (this->mappert.find(lookahead) != mappert.end()) ? mappert[lookahead] : getToken(lookahead);
			if (lookaheadToken == Token::IDENTIFIER)
			{
				if (std::find(Identifiers.begin(), Identifiers.end(), lookahead) != Identifiers.end())
				{
					ErrorHandler::getInstance()->addError(Error{ "identifier '" + lookahead + "' is already defined", "unknown.MD", rowNr, colNr, Error::errorType::error });
				}
				pToken->setSub(currentToken);
				currentToken = lookaheadToken;
				Identifiers.push_back(lookahead);
				//skip types direct, zodat later identief geskipped word, zijn beide al gedaan
				part = lookahead;
				s = m.suffix().str();
				regex_search(s, m, e);
				
			}
			else
			{
				ErrorHandler::getInstance()->addError(Error{ "Expected an identifier", "unknown.MD", rowNr, colNr, Error::errorType::error });
			}
		}
		else if (currentToken == Token::IDENTIFIER)
		{
			if (!(std::find(Identifiers.begin(), Identifiers.end(), part) != Identifiers.end()))
			{
				ErrorHandler::getInstance()->addError(Error{ "identifier '" + part + "' is undefined", "unknown.MD", rowNr, colNr, Error::errorType::error });
			}
		}
		else if (currentToken == Token::NEWLINE || currentToken == Token::COMMENT) //New Lines
		{
			colNr = 1; rowNr++;
		}
		
		pToken->setText((part));
		pToken->setLevel(lvl);
		pToken->setPositie(colNr);
		pToken->setPositieInList(cTokenList.size());
		pToken->setRegelnummer(rowNr);
		pToken->setEnum(currentToken);
		pToken->setPartner(nullptr);

		//Add + Next
		cTokenList.add(pToken);

		//Levels
		if (currentToken == Token::BODY_OPEN || currentToken == Token::CONDITION_OPEN || currentToken == Token::FUNCTION_OPEN)
		{
			lvl++;
		}

		//++ col
		colNr += part.size() + 1;

		////Levels
		if (currentToken == Token::BODY_CLOSED || currentToken == Token::CONDITION_CLOSE || currentToken == Token::FUNCTION_CLOSE)
		{
			lvl--;
		}

		CheckStack(*pToken, lvl);

		s = m.suffix().str();
	}

	CheckRemainingStack();
	checkRemainingErrors();
}

std::string Tokenizer::lookAhead(smatch m, std::string s)
{
	smatch m2;
	std::string lookahead = m.suffix().str();
	regex_search(lookahead, m2, e);
	return m2[0];
}


void Tokenizer::checkRemainingErrors()
{
	if (this->stack.size() > 0)
	{
		tokenError = true;
		while (this->stack.size() > 0)
		{
			Token* token = this->stack.top();
			this->stack.pop();
			token->addError();
		}
	}
}

void Tokenizer::printTokenList(LinkedList& cTokenList)
{
	Text::PrintLine("POSITIELIJST - REGELNR - POSITIE - TEXT - LEVEL - PARTNER");
	Token* start = cTokenList.first;
	while (start != nullptr){
		start->Print(this->mappert);
		start = start->next;
	}
}

void Tokenizer::CheckRemainingStack(){
	if (this->stack.size() > 0 && (this->stack.top()->getEnum() == Token::IF || this->stack.top()->getEnum() == Token::ELIF)){
		this->stack.pop();
	}
}


void Tokenizer::CheckStack(Token& token, int &lvl){
	CheckCondition(token, lvl);
	CheckBrackets(token, lvl);
};

void Tokenizer::CheckCondition(Token& token, int &lvl){
	if (token.getEnum() == Token::DO)
	{
		this->stack.push(&token);
	}
	if (token.getEnum() == Token::WHILE){
		if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::DO){
			Token* stackToken = this->stack.top();
			token.setPartner(stackToken);
			stackToken->setPartner(&token);
			this->stack.pop();
		}
	}
	if (token.getEnum() == Token::IF)
	{
		if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::IF)
		{
			this->stack.pop();
		}
		this->stack.push(&token);
	}
	if (token.getEnum() == Token::ELSE)
	{
		if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::IF)
		{
			Token* stackToken = this->stack.top();
			token.setPartner(stackToken);
			stackToken->setPartner(&token);
			this->stack.pop();
		}
		else if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::ELIF)
		{
			Token* stackToken = this->stack.top();
			Token* partner = stackToken->getPartner();
			if (partner == nullptr){
				this->stack.push(&token);
			}
			else{
				while (partner->getEnum() != Token::IF){
					partner = partner->getPartner();
				}
				token.setPartner(partner);
				stackToken->setPartner(&token);
				this->stack.pop();
			}

		}
		else{
			this->stack.push(&token);
		}
	}
	if (token.getEnum() == Token::ELIF)
	{
		if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::IF)
		{
			Token* stackToken = this->stack.top();
			token.setPartner(stackToken);
			stackToken->setPartner(&token);
			this->stack.pop();
			this->stack.push(&token);
		}
		else if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::ELIF)
		{
			Token* stackToken = this->stack.top();
			Token* partner = stackToken->getPartner();
			if (partner != nullptr){
				while (partner->getEnum() != Token::IF){
					partner = partner->getPartner();
				}
				token.setPartner(partner);
				stackToken->setPartner(&token);
				this->stack.pop();
			}
			this->stack.push(&token);
		}
		else{
			this->stack.push(&token);
		}
	}
};

void Tokenizer::CheckBrackets(Token& token, int &lvl)
{
	if (token.getEnum() == Token::BODY_OPEN || token.getEnum() == Token::CONDITION_OPEN || token.getEnum() == Token::FUNCTION_OPEN || token.getEnum() == Token::ARRAY_OPEN )
	{
		this->stack.push(&token);
	}
	else if (token.getEnum() == Token::BODY_CLOSED || token.getEnum() == Token::CONDITION_CLOSE || token.getEnum() == Token::FUNCTION_CLOSE || token.getEnum() == Token::ARRAY_CLOSE )
	{
		if (this->stack.size() > 0)
		{
			if ((token.getEnum() == Token::BODY_CLOSED && this->stack.top()->getEnum() == Token::IF) && token.getLevel() == this->stack.top()->getLevel())
			{
				if (token.next != nullptr)
				{
					if (token.next->getEnum() != Token::ELSE)
					{
						this->stack.pop();
					}
				}
			}
			if ((token.getEnum() == Token::BODY_CLOSED && this->stack.top()->getEnum() == Token::BODY_OPEN) ||
				(token.getEnum() == Token::FUNCTION_CLOSE && this->stack.top()->getEnum() == Token::FUNCTION_OPEN) ||
				(token.getEnum() == Token::ARRAY_CLOSE && this->stack.top()->getEnum() == Token::ARRAY_OPEN) ||
				(token.getEnum() == Token::CONDITION_CLOSE && this->stack.top()->getEnum() == Token::CONDITION_OPEN))
			{
				token.setLevel(lvl);
				Token* stackToken = this->stack.top();
				token.setPartner(stackToken);
				stackToken->setPartner(&token);
				this->stack.pop();
			}
		}
	}
};


Token::iToken Tokenizer::getToken(std::string token)
{
	smatch m;
	typedef std::map<std::string, Token::iToken>::iterator it_type;
	for (it_type iterator = regexert.begin(); iterator != regexert.end(); iterator++) 
	{
		regex e(iterator->first);
		regex_search(token, m, e);
		if (m.size() != 0)
		{
			return iterator->second;
		}

	}
	return Token::NONE;
}

std::string Tokenizer::getKeywordsAsJson()
{
	std::string JSON = "[";
	int size = (int)mappert.size();
	int i = 0;
	for (std::map<std::string, Token::iToken>::iterator it = mappert.begin(); it != mappert.end(); ++it)
	{
		if ((*it).second == Token::NEWLINE)
		{
			i++;
			continue;
		}
		JSON += "{\"keyword\":\"" + (*it).first + "\"}";

		if (i < size - 1)
			JSON += ",";
		i++;
	}
	JSON += "]";
	return JSON;
}


Tokenizer::~Tokenizer()
{
}
