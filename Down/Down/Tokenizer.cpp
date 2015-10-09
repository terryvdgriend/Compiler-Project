#include "stdafx.h"
#include "Tokenizer.h"
#include "Format.h"
#include <iostream>

Tokenizer::Tokenizer()
{
	//
}

void Tokenizer::createTokenList(Token::TokenList& cTokenList, string codefromfile)
{
	Token  *pToken;
	std::vector<string> codeSplit =  Format::split(codefromfile, '\n');

	// VOORBEELD CODE: aanmaken van Token en stoppen op de 'stack'
	pToken = new Token;
	pToken->setText("x");
	pToken->setEnum(Token::IDENTIFIER);
	cTokenList.push_back(pToken);
	//END


	int rowNr = 1;
	int colNr = 1;
	//voor elke rij
	for (vector<string>::iterator lines = codeSplit.begin(); lines != codeSplit.end(); ++lines)
	{
		vector<string> rows = Format::split((*lines), ' ');
		for (std::vector<string>::iterator rws = rows.begin(); rws != rows.end(); ++rws)
		{
			std::cout << (*rws);
		}

		
	}
}

Tokenizer::~Tokenizer()
{
}
