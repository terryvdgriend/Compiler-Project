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
	std::map<string, Token::iToken> varTokenMap;
	Stack stack;
	Token::iToken getToken(std::string token);
	Token::iToken tempToken;
	bool tokenError = false;
	Token::iToken getNextToken(smatch & m, string & s);
	void checkRemainingErrors();
	//Omdat else if als eerst staat zal deze gekozen worden..  nasty work around.
        
    // (\*{2}\S+?\*{2}|#+ (?:else if|\w+)|and gives|multiplied by|^>.*\n|(\w+) than|^-?\d*\.?\d*$|"(.*?)"|\w+|-{1,3}|[\S|\n])
	regex e{ "(\\*{2}\\S+?\\*{2}|#+ (?:else if|\\w+)|and gives|multiplied by|(>.*)|(like or )?(\\w+) than|^-?\\d.?\\d*$|\"(.*?)\"|\\w+|-{1,3}|[\\S|\\n])" };
	void lookAheadMethod(smatch & m, string & s, Token & pToken, Token::iToken & currentToken, string & part, int rowNr, int colNr, bool arrayOpen);
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
