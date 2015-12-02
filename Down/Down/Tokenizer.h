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
	typedef std::stack<Token*>   Stack;
private: 
	std::map<string, Token::iToken> mappert;
	std::map<string, Token::iToken> regexert;
	std::map<string, Token::iToken> Regex;
	int currentScope = 0;
	int maxScope = 0;
	Stack stack;
	Token::iToken getToken(std::string token);
	bool tokenError = false;
	void checkRemainingErrors();
	//Omdat else if als eerst staat zal deze gekozen worden..  nasty work around.
        
    // (#+ (?:else if|else|if|case|while|do|foreach|for|\w+)|and gives|multiplied by|(^>.*\n)|(smaller|larger) than|^-?\d.?\d*$|"(.*?)"|\w+|\*\*\S*?\*\*|-{1,3}|^[\(\)\[\]]$|[\S|\n])
	regex e{ "(#+ (?:else if|else|if|case|while|do|foreach|for|\\w+)|and gives|multiplied by|(^>.*\\n)|(smaller|larger) than|^-?\\d.?\\d*$|\"(.*?)\"|\\w+|\\*\\*\\S*?\\*\\*|-{1,3}|^[\\(\\)\\[\\]]$|[\\S|\\n])" };
	std::string lookAhead(smatch m, std::string s);
public:
	Tokenizer();
	void createTokenList(LinkedList& cTokenList, string codefromfile);
	void printTokenList(LinkedList& cTokenList);
	void CheckStack(Token& token, int& lvl);
	void CheckCondition(Token& token, int& lvl);
	void CheckBrackets(Token& token, int& lvl);
	void CheckRemainingStack();
	bool GetTokenError() { return tokenError; };

	std::string getKeywordsAsJson();
	std::string getFunctionsAsJson();
	std::string getKeyByValueMappert(Token::iToken tkn);
	~Tokenizer();
};
