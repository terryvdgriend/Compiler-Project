#include "stdafx.h"
#include "Tokenizer.h"
#include "Format.h"
#include <iostream>
#include <regex>

Tokenizer::Tokenizer()
{
	//System only
	mappert["\n"] = Token::NEWLINE;

	// Think again map
	mappert2[std::regex("\\*\\*.+\\*\\*")] = Token::IDENTIFIER;
	mappert2[std::regex("\d+")] = Token::NUMBER;
	
	// First Map
	mappert["###"] = Token::CLASS;
	mappert["#### if"] = Token::IF;
	mappert["#### else"] = Token::ELSE;
	mappert["#### else if"] = Token::ELIF;
	mappert["___"] = Token::BODY_CLOSED;
	mappert["---"] = Token::BODY_OPEN;
	mappert["is"] = Token::EQUALS;
	mappert["like"] = Token::EQUALS_TO;
	// klopt niet: moeten de types zijn
	mappert["_number_"] = Token::NUMBER;
	mappert["_text_"] = Token::TEXT;
	mappert["_fact_"] = Token::BOOL;
	//Reken dingen
	mappert["plus"] = Token::PLUS;
	mappert["minus"] = Token::MINUS;
	mappert["divide"] = Token::DIVIDE;
	mappert["multiply"] = Token::TIMES;
	mappert["modulo"] = Token::NONE;
}

void Tokenizer::createTokenList(Token::TokenList& cTokenList, string codefromfile)
{
	Token  *pToken;
	Token::Stack stack;

	string s(codefromfile);
	smatch m;
	regex e("(#+ (?:else if|else|if|case)|\\w+|\\S+|\n)");
	//regex se("\\*\\*.+\\*\\*");
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
		//smatch sm;
		//regex_search(part, sm, se);
		//if (sm.size() != 0)
		//currentToken = Token::IDENTIFIER;
		//currentToken = mappert2[std::regex("\\*\\*.+\\*\\*")];
		//mappert2[se];

		currentToken = mappert[part];
		if (currentToken = Token::NONE)
		{
			currentToken = thinkAgain(part);
		}

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

Token::iToken Tokenizer::thinkAgain(std::string str)
{
	Token::iToken tokkie;
	for (map<regex, Token::iToken>::iterator tt = mappert2.begin(); tt != mappert2.end(); tt++)
	{

	}
	return tokkie;
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
