#pragma once
#include "LinkedTokenList.h"
#include "BaseCommand.h"

class Function
{
	public:
		Function(string functionName, string params, shared_ptr<LinkedTokenList> body, vector<shared_ptr<Token>>& paramTokens, shared_ptr<Token> returnToken);
		Function(string functionName, string params, shared_ptr<LinkedTokenList> body, vector<shared_ptr<Token>>& paramTokens, shared_ptr<Token> returnToken, bool userDefined);
		Function(string functionName, string params, shared_ptr<BaseCommand> c, vector<shared_ptr<Token>>& paramTokens);

		string getName();
		string getParams();
		vector<shared_ptr<Token>>& getParamTokens();
		shared_ptr<LinkedTokenList> getBody();
		shared_ptr<Token> getReturn();
		shared_ptr<BaseCommand> getCommand() {	return _bc;};
		bool isUserDefined();

	private:
		string _name;
		string _params;
		vector<shared_ptr<Token>> _paramTokens;
		shared_ptr<LinkedTokenList> _body;
		shared_ptr<Token> _returnToken;
		shared_ptr<BaseCommand> _bc;
		bool _userDefined;
};