#include "stdafx.h"
#include "Tokenizer.h"
#include "Format.h"
#include "LinkedList.h"
#include <iostream>
#include <regex>

Tokenizer::Tokenizer()
{
	//
	mappert["\n"] = Token::NEWLINE;
	// 
	mappert["secret"] = Token::PRIVATE;
	mappert["#### if"] = Token::IF;
	mappert["#### else"] = Token::ELSE;
	mappert["#### else if"] = Token::ELIF;
	mappert["#### for"] = Token::FOR;
	mappert["#### foreach"] = Token::FOREACH;
	mappert["#### while"] = Token::WHILE;
	mappert["#### do"] = Token::DO;
	mappert["---"] = Token::FUNCTION_OPEN;
	mappert["___"] = Token::FUNCTION_CLOSE;
	mappert["("] = Token::CONDITION_OPEN;
	mappert[")"] = Token::CONDITION_CLOSE;
	mappert["{"] = Token::BODY_OPEN;
	mappert["}"] = Token::BODY_CLOSED;
	//
	mappert["is"] = Token::EQUALS;
	mappert["like"] = Token::EQUALS_TO;
	mappert["smaller than"] = Token::LESS_THAN;
	mappert["larger than"] = Token::LARGER_THAN;
	mappert["in"] = Token::IN;
	//
	mappert["_number_"] = Token::NUMBER;
	mappert["_text_"] = Token::TEXT;
	mappert["_fact_"] = Token::BOOL;
	mappert["_variable_"] = Token::IDENTIFIER;
	mappert[","] = Token::SEPARATOR;
	mappert["_declarition_"] = Token::DECLARATION;
	mappert["_function_"] = Token::FUNCTION;
	mappert["_class_"] = Token::CLASS;
	mappert["_namespace_"] = Token::NAMESPACE;
	//
	mappert["plus"] = Token::PLUS;
	mappert["increased"] = Token::PLUSPLUS;
	mappert["minus"] = Token::MINUS;
	mappert["decreased"] = Token::MINUSMINUS;
	mappert["divide"] = Token::DIVIDE;
	mappert["multiply"] = Token::TIMES;
	mappert["modulo"] = Token::MODULO;
	//
	//mappert["\\*\\*.+\\*\\*"] = Token::IDENTIFIER;


	regexert[std::string("\\d")] = Token::NUMBER;
	regexert[std::string("\".*?\"")] = Token::TEXT;
	regexert[std::string("(true|false)")] = Token::BOOL;
	regexert[std::string("\\*\\*(\\w*)?\\*\\*")] = Token::IDENTIFIER;
	regexert[std::string("(_(\\w*)_)")] = Token::DECLARATION;
	regexert[std::string("(# (\\w*))")] = Token::NAMESPACE;
	regexert[std::string("(## (\\w*))")] = Token::CLASS;
	regexert[std::string("(### (\\w*):)")] = Token::FUNCTION;

}

void Tokenizer::createTokenList(LinkedList& cTokenList, string codefromfile)
{
	Token  *pToken;

	string s(codefromfile);
	smatch m;
	regex e("(#+ (?:else if|else|if|case|while|do|foreach|for)|(smaller|larger) than|\\w+|\\S+|\n)");
	regex se("\\*\\*.+\\*\\*");
	// (#+ (?:else if|else|if|case)|\w+|\S+)
	// M: (""|'.'\d+\.\d+|\w|\S|\n)
	// 

	int rowNr = 1;
	int colNr = 1;
	int lvl = 1;
	int pInt = 0;
	Token *prevToken;
	while (regex_search(s, m, e))
	{
		pToken = new Token;
		Token::iToken currentToken;
		string part = m[0];
		//Check identifier
		smatch sm;
		regex_search(part, sm, se);
		if (sm.size() != 0)
			currentToken = Token::IDENTIFIER;
		else
			currentToken = (mappert.find(part) == mappert.end()) ? getToken(part) : mappert[part];

		//New Lines
		if (currentToken == Token::NEWLINE)
		{
			colNr = 1;
			rowNr++;
			s = m.suffix().str();
			continue;
		}

		

		
		pToken->setText((part));
		pToken->setLevel(lvl); 
		pToken->setPositie(colNr);
		pToken->setPositieInList(pInt);
		pToken->setRegelnummer(rowNr);
		pToken->setEnum(currentToken);

		//Add + Next
		cTokenList.add(pToken);



		//Levels
		if (currentToken == Token::BODY_OPEN || currentToken == Token::CONDITION_OPEN || currentToken == Token::FUNCTION_OPEN)
		{
			lvl++;
		}

		//++ col
		colNr += part.size() + 1;
		pInt++;
		
		////Levels
		if (currentToken == Token::BODY_CLOSED || currentToken == Token::CONDITION_CLOSE || currentToken == Token::FUNCTION_CLOSE)
		{
			lvl--;
		}

		CheckStack(*pToken, lvl);

		s = m.suffix().str();
		prevToken = pToken;
	}
	CheckRemainingStack();
}

void Tokenizer::printTokenList(LinkedList& cTokenList)
{
	if (this->stack.size() > 0){
		tokenError = true;
		while (this->stack.size() > 0){
			Token* token = this->stack.top();
			this->stack.pop();
			token->PrintError();
		}
	}
	else{
		Text::PrintLine("POSITIELIJST - REGELNR - POSITIE - TEXT - LEVEL - PARTNER");
		Token* start = cTokenList.first;
		while (start != nullptr){
			start->Print(this->mappert);
			start = start->next;
		}
	}
}

void Tokenizer::CheckRemainingStack(){
	if (this->stack.size() > 0 && this->stack.top()->getEnum() == Token::IF){
		this->stack.pop();
	}
}


void Tokenizer::CheckStack(Token& token, int &lvl){
	CheckCondition(token,  lvl);
	CheckBrackets(token, lvl);
};

void Tokenizer::CheckCondition(Token& token, int &lvl){
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
			while (partner->getEnum() != Token::IF){
				partner = partner->getPartner();
			}
			token.setPartner(partner);
			stackToken->setPartner(&token);
			this->stack.pop();
			this->stack.push(&token);
		}
		else{
			this->stack.push(&token);
		}
	}
};

void Tokenizer::CheckBrackets(Token& token,int &lvl)
{
	if (token.getEnum() == Token::BODY_OPEN || token.getEnum() == Token::CONDITION_OPEN)
	{
		this->stack.push(&token);
	}
	else if (token.getEnum() == Token::BODY_CLOSED || token.getEnum() == Token::CONDITION_CLOSE)
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

Token::iToken Tokenizer::getToken(std::string token){
	typedef std::map<std::string, Token::iToken>::iterator it_type;
	for (it_type iterator = regexert.begin(); iterator != regexert.end(); iterator++) {
		smatch m;
		regex e(iterator->first);
		regex_search(token, m, e);
		if (m.size() != 0)
		{
			return iterator->second;
		}

	}
	return Token::NONE;	
}


Tokenizer::~Tokenizer()
{

}
