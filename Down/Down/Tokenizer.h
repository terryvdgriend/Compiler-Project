#pragma once
#include "Token.h"
#include <list>

class Tokenizer
{
private: 
	std::map<string, Token::iToken> mappert;
	std::list<string> errnoez;

	void checkStack();
public:
	Tokenizer();
	void createTokenList(Token::TokenList& cTokenList, string codefromfile);
	void printTokenList(Token::TokenList& cTokenList);
	Token::iToken getEnumByString(string name, bool &isDone);
	std::list<string> getErrors(){ return errnoez; };
	~Tokenizer();
};

