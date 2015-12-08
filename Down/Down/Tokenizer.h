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
	std::map<string, Token::iToken> mappert;
	std::map<string, Token::iToken> regexert;
	std::map<string, Token::iToken> Regex;
	int currentScope = 0;
	int maxScope = 0;
	std::map<string, Token::iToken> varTokenMap;
	Stack stack;
	Token::iToken getToken(string token);
	bool tokenError = false;
	Token::iToken getNextToken(smatch & m, string & s);
	void checkRemainingErrors();
	//Omdat else if als eerst staat zal deze gekozen worden..  nasty work around.
        
    // (#+ (?:else if|else|if|case|while|do|foreach|for|\w+)|and gives|multiplied by|(^>.*\n)|(smaller|larger) than|^-?\d.?\d*$|"(.*?)"|\w+|\*\*\S*?\*\*|-{1,3}|^[\(\)\[\]]$|[\S|\n])
	regex e{ "(#+ (?:else if|else|if|case|while|do|foreach|for|\\w+)|and gives|multiplied by|(^>.*\\n)|(like or )?(smaller|larger) than|^-?\\d.?\\d*$|\"(.*?)\"|\\w+|\\*\\*\\S*?\\*\\*|-{1,3}|^[\\(\\)\\[\\]]$|[\\S|\\n])" };
	std::string lookAhead(smatch m, std::string s);
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
	string getFunctionsAsJson();
	string getKeyByValueMappert(Token::iToken tkn);
	~Tokenizer();
};
