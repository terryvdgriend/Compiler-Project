#pragma once
#include "Token.h"
#include "LinkedTokenList.h"

class Tokenizer
{
	public:
		typedef stack<shared_ptr<Token>> Stack;

		Tokenizer();

		void createTokenList(shared_ptr<LinkedTokenList>& tokenList, const string codefromfile);
		void printTokenList(shared_ptr<LinkedTokenList>& tokenList);

		bool getTokenError();
		string getKeywordsAsJson();
		string getFunctionsAsJson();
		string getKeyByValueTokenMap(IToken tokenType);

	private: 
		map<string, IToken> tokenMap;
		map<string, IToken> tokenRegex;
		map<string, IToken> regexMap;
		map<string, IToken> varTokenMap;
		regex actualRegex;
		int currentScope;
		int maxScope;
		Stack stack;
		bool tokenError;
		IToken tempToken;

		void checkStack(shared_ptr<Token>& token, int& lvl);
		void checkCondition(shared_ptr<Token>& token, int& lvl);
		void checkBrackets(shared_ptr<Token>& token, int& lvl);
		void checkRemainingStack();
		void checkRemainingErrors();

		string lookAhead(smatch match);
		void lookAheadMethod(smatch& match, string& codePart, shared_ptr<Token>& token, IToken& currentToken, string& part, int rowNr, int colNr, bool arrayOpen);

		IToken getToken(string token);
		IToken getNextToken(smatch& match, string& codePart);
};