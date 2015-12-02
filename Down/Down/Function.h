#pragma once
#include "LinkedList.h"

class Function
{
	public:
		Function(string functionName, string params, shared_ptr<LinkedList> body, shared_ptr<vector<shared_ptr<Token>>> paramTokens, shared_ptr<Token> returnToken);
		Function(string functionName, string params, shared_ptr<LinkedList> body, shared_ptr<vector<shared_ptr<Token>>> paramTokens, shared_ptr<Token> returnToken, bool userDefined);

		string getName();
		string getParams();
		shared_ptr<vector<shared_ptr<Token>>> getParamTokens();
		shared_ptr<LinkedList> getBody();
		shared_ptr<Token> getReturn();
		bool isUserDefined();

	private:
		string _name;
		string _params;
		shared_ptr<vector<shared_ptr<Token>>> _paramTokens;
		shared_ptr<LinkedList> _body;
		shared_ptr<Token> _returnToken;
		bool _userDefined;
};