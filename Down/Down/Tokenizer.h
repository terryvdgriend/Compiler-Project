#pragma once
#include "Token.h"
#include "LinkedList.h"

class Tokenizer
{
	public:
		typedef stack<shared_ptr<Token>> Stack;

		Tokenizer();

		void createTokenList(shared_ptr<LinkedList>& tokenList, string codefromfile);
		void printTokenList(shared_ptr<LinkedList>& tokenList);

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