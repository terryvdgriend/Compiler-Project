#pragma once
#include "LinkedList.h"

class Function
{
	public:
		Function(string functionName, string params, shared_ptr<LinkedList> body, vector<shared_ptr<Token>>& paramTokens, shared_ptr<Token> returnToken);
		Function(string functionName, string params, shared_ptr<LinkedList> body, vector<shared_ptr<Token>>& paramTokens, shared_ptr<Token> returnToken, bool userDefined);

		string getName();
		string getParams();
		vector<shared_ptr<Token>>& getParamTokens();
		shared_ptr<LinkedList> getBody();
		shared_ptr<Token> getReturn();
		bool isUserDefined();

	private:
		string _name;
		string _params;
		vector<shared_ptr<Token>> _paramTokens;
		shared_ptr<LinkedList> _body;
		shared_ptr<Token> _returnToken;
		bool _userDefined;
};