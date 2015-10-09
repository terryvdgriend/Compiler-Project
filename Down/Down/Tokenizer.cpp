#include "stdafx.h"
#include "Tokenizer.h"
#include "Format.h"
#include <iostream>
#include <regex>

Tokenizer::Tokenizer()
{
	// Incomplete cases
	mappert["#### if"] = Token::IF;
	mappert["#### else"] = Token::ELSE;
	mappert["#### else if"] = Token::ELIF;
	mappert["___"] = Token::BODY_OPEN;
	mappert["is"] = Token::EQUALS;
	mappert["like"] = Token::EQUALS_TO;
}

void Tokenizer::createTokenList(Token::TokenList& cTokenList, string codefromfile)
{
	Token  *pToken;
	
	string s(codefromfile);
	smatch m;
	regex e("(#+ (?:else if|else|if|case)|\\w+|\\S+)"); 
	// (#+ (?:else if|else|if|case)|\w+|\S+)

	int rowNr = 1;
	int colNr = 1;
	bool isBodyOpen = false;
	bool isDone = false;
	Token::iToken previousToken;

	while (regex_search(s, m, e))
	{
		string part = m[0];
		Token::iToken currentToken = mappert[part];

		

		pToken = new Token;
		pToken->setText((part));
		pToken->setEnum(currentToken);
		cTokenList.push_back(pToken);

		//Next
		s = m.suffix().str();
	}
}

void Tokenizer::printTokenList(Token::TokenList& cTokenList)
{
	for (std::list<Token *>::iterator it = cTokenList.begin(); it != cTokenList.end(); it++)
	{
		Token *tokkie = (*it);
		cout << ">> " + tokkie->getText() + "\n";

	}
}


Tokenizer::~Tokenizer()
{
	/*vector<string> rows = Format::split((*lines), ' ');
	for (std::vector<string>::iterator rws = rows.begin(); rws != rows.end(); ++rws)
	{*/

	/*bool butwait = true;
	while (butwait)
	{
	s = m.suffix().str();
	regex_search(s, m, e);
	string part2 = m[0];
	Token::iToken datToken2 = mappert[part2];
	if (datToken2 == Token::IF)
	part = part + part2;
	}*/

	/*
	if (currentToken == Token::NIV4)
		{
			previousToken = currentToken;
			continue;
		}
		if (currentToken == Token::ELSE && previousToken == Token::NIV4)
		{
			// na ELSE kan nog ELSE IF komen
		}
		if (!(currentToken == Token::IF || currentToken == Token::ELSE) && previousToken == Token::NIV4)
		{
			errnoez.push_back("must have IF or ELSE on line X col X");
			continue;
		}
	*/

}
