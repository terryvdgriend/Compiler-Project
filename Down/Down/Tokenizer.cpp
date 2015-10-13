#include "stdafx.h"
#include "Tokenizer.h"
#include "Format.h"
#include <iostream>
#include <regex>

Tokenizer::Tokenizer()
{
	//
	mappert["\n"] = Token::NEWLINE;
	// 
	mappert["###"] = Token::CLASS;
	mappert["#### if"] = Token::IF;
	mappert["#### else"] = Token::ELSE;
	mappert["#### else if"] = Token::ELIF;
	mappert["___"] = Token::BODY_CLOSED;
	mappert["---"] = Token::BODY_OPEN;
	mappert["is"] = Token::EQUALS;
	mappert["like"] = Token::EQUALS_TO;
	//
	mappert["_number_"] = Token::NUMBER;
	mappert["_text_"] = Token::TEXT;
	mappert["_fact_"] = Token::BOOL;
	//
	mappert["plus"] = Token::PLUS;
	mappert["minus"] = Token::MINUS;
	mappert["divide"] = Token::DIVIDE;
	mappert["multiply"] = Token::TIMES;
	mappert["modulo"] = Token::NONE;
	//
	//mappert["\\*\\*.+\\*\\*"] = Token::IDENTIFIER;
}

void Tokenizer::createTokenList(Token::TokenList& cTokenList, string codefromfile)
{
	Token  *pToken;
	Token::Stack stack;

	string s(codefromfile);
	smatch m;
	regex e("(#+ (?:else if|else|if|case)|\\w+|\\S+|\n)");
	regex se("\\*\\*.+\\*\\*");
	// (#+ (?:else if|else|if|case)|\w+|\S+)
	// M: (""|'.'\d+\.\d+|\w|\S|\n)
	// 

	int rowNr = 1;
	int colNr = 1;
	int lvl = 1;

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
			currentToken = mappert[part];

		//New Lines
		if (currentToken == Token::NEWLINE)
		{
			colNr = 1;
			rowNr++;
			s = m.suffix().str();
			continue;
		}

		//Levels
		if (currentToken == Token::BODY_OPEN)
		{
			lvl++;
			stack.push_front(pToken);
		}

		
		pToken->setText((part));
		pToken->setLevel(lvl); 
		pToken->setPositie(colNr);
		pToken->setPositieInList(3);
		pToken->setRegelnummer(rowNr);
		pToken->setEnum(currentToken);
		

		//++ col
		colNr += part.size() + 1;
		
		//Levels
		if (currentToken == Token::BODY_CLOSED)
		{
			lvl--;
			//Token tok = *cTokenList.back();
			//pToken->setPartner(tok); // TODO
			stack.pop_front();
		}

		//Add + Next
		cTokenList.push_back(pToken);
		s = m.suffix().str();
	}
}

void Tokenizer::printTokenList(Token::TokenList& cTokenList)
{
	Text::PrintLine("TEXT - REGELNR - COLNR - LEVEL - PARTNAH");
	for (std::list<Token *>::iterator it = cTokenList.begin(); it != cTokenList.end(); it++)
		(*it)->Print();

}


Tokenizer::~Tokenizer()
{

}
