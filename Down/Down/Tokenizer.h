#pragma once
#include "Token.h"
#include "LinkedTokenList.h"

class Tokenizer
{
	public:
		typedef stack<shared_ptr<Token>> Stack;

		Tokenizer();

		void createTokenList(shared_ptr<LinkedTokenList>& tokenList, string codefromfile);
		void printTokenList(shared_ptr<LinkedTokenList>& tokenList);

		bool getTokenError();
		string getKeywordsAsJson();
		string getFunctionsAsJson();
		string getKeyByValueTokenMap(IToken type);

	private: 
		map<string, IToken> tokenMap;
		map<string, IToken> tokenRegex;
		map<string, IToken> regexMap;
		regex actualRegex;
		int currentScope;
		int maxScope;
		Stack stack;
		bool tokenError;

		void checkStack(shared_ptr<Token>& token, int& lvl);
		void checkCondition(shared_ptr<Token>& token, int& lvl);
		void checkBrackets(shared_ptr<Token>& token, int& lvl);
		void checkRemainingStack();
		void checkRemainingErrors();

		IToken getToken(string token);
		string lookAhead(smatch m, string s);
};