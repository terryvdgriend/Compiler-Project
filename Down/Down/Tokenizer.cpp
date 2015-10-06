#include "stdafx.h"
#include "Tokenizer.h"

#include <iostream>

Tokenizer::Tokenizer()
{
	//
}

void Tokenizer::createTokenList(Token::TokenList& cTokenList, std::vector<string> codeSplit)
{
	Token  *pToken;


	// VOORBEELD CODE: aanmaken van Token en stoppen op de 'stack'
	pToken = new Token;
	pToken->setText("x");
	pToken->setEnum(Token::IDENTIFIER);
	cTokenList.push_back(pToken);

	pToken = new Token;
	pToken->setText("+");
	pToken->setEnum(Token::PLUS);
	cTokenList.push_back(pToken);

	//
	for (std::vector<string>::iterator it = codeSplit.begin(); it != codeSplit.end(); ++it) 
	{
		string keyword = (*it);

		std::cout << (*it);
	}
}

Tokenizer::~Tokenizer()
{
}
