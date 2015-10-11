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
	mappert["**whut**"] = Token::IDENTIFIER;
}

void Tokenizer::createTokenList(Token::TokenList& cTokenList, string codefromfile)
{
	Token  *pToken;
	Token::Stack stack;

	string s(codefromfile);
	smatch m;
	regex e("(#+ (?:else if|else|if|case)|\\w+|\\S+|\n)");
	// (#+ (?:else if|else|if|case)|\w+|\S+)
	// M: (""|'.'\d+\.\d+|\w|\S|\n)
	// 

	int rowNr = 1;
	int colNr = 1;
	int lvl = 1;

	while (regex_search(s, m, e))
	{
		string part = m[0];
		Token::iToken currentToken = mappert[part];

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
			//Token tok = stack.front();
		}

		pToken = new Token;
		pToken->setText((part));
		pToken->setLevel(lvl); // {} deep
		pToken->setPositie(colNr);
		pToken->setPositieInList(3);
		pToken->setRegelnummer(rowNr);
		//pToken->setPartner(&cTokenList.back()); // TODO
		pToken->setEnum(currentToken);
		cTokenList.push_back(pToken);

		//++ col
		colNr += part.size() + 1;
		
		//Levels
		if (currentToken == Token::BODY_CLOSED)
		{
			lvl--;
		}

		//Next
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
