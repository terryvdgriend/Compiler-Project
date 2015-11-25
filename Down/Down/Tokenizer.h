#pragma once
#include "Token.h"
#include "LinkedList.h"
#include <list>
#include <stack>
#include <iostream>
#include <regex>
//
class Tokenizer
{
public:
	typedef stack<Token*>   Stack;
private: 
	map<string, Token::iToken> mappert;
	map<string, Token::iToken> regexert;
	map<string, Token::iToken> Regex;
	Stack stack;
	Token::iToken getToken(string token);
	bool tokenError = false;
	void checkRemainingErrors();
	//Omdat else if als eerst staat zal deze gekozen worden..  nasty work around.
	regex e{ "(#+ (?:else if|else|if|case|while|do|foreach|for|\\w+)|and gives|multiplied by|(^>.*\n)|(smaller|larger) than|-?\\d\\.?\\d*|\"(.*?)\"|\\w+|\\S+|\n)" };
	string lookAhead(smatch m, string s);

	void lookAheadMethod(smatch& m, string& s, Token& pToken, Token::iToken& currentToken, string& part, int rowNr, int colNr, bool arrayOpen);
	Token::iToken tempToken;
public:
	Tokenizer();
	void createTokenList(LinkedList& cTokenList, string codefromfile);
	void printTokenList(LinkedList& cTokenList);
	void CheckStack(Token& token, int& lvl);
	void CheckCondition(Token& token, int& lvl);
	void CheckBrackets(Token& token, int& lvl);
	void CheckRemainingStack();
	bool GetTokenError() { return tokenError; };

	string getKeywordsAsJson();
	string getKeyByValueMappert(Token::iToken tkn);
	~Tokenizer();
};

