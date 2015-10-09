#pragma once
#include "Token.h"


class Tokenizer
{
public:
	Tokenizer();
	void createTokenList(Token::TokenList& cTokenList, string codefromfile);
	~Tokenizer();
};

