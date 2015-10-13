#pragma once
#include "Token.h"
#include <list>

class Tokenizer
{
private: 
	std::map<string, Token::iToken> mappert;
	std::map<regex, Token::iToken> mappert2;
	std::list<string> errnoez;
	Token::iToken thinkAgain(std::string str);
	void checkStack();
public:
	Tokenizer();
	void createTokenList(Token::TokenList& cTokenList, string codefromfile);
	void printTokenList(Token::TokenList& cTokenList);
	Token::iToken getEnumByString(string name, bool &isDone);
	std::list<string> getErrors(){ return errnoez; };
	~Tokenizer();
};

