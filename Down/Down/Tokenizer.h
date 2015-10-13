#pragma once
#include "Token.h"
#include "LinkedList.h"
#include <list>
#include <stack>

class Tokenizer
{
public:
	typedef std::stack<Token*>   Stack;
private: 
	std::map<string, Token::iToken> mappert;
	std::list<string> errnoez;
	Stack stack;
	void checkStack();
public:
	Tokenizer();
	void createTokenList(LinkedList& cTokenList, string codefromfile);
	void printTokenList(LinkedList& cTokenList);
	void CheckStack(Token& token, int& lvl);
	void CheckCondition(Token& token, int& lvl);
	void CheckBrackets(Token& token, int& lvl);
	Token::iToken getEnumByString(string name, bool &isDone);
	std::list<string> getErrors(){ return errnoez; };
	~Tokenizer();
};

