#pragma once
#include "LinkedActionList.h"

class Function
{
private:
	std::string _naam;
	std::string _params;
	std::vector<Token*> _paramTokens;
	Token* _returnToken;
	LinkedList* _body;
	bool _userdef = false;
public:
	Function(string naam, string params, LinkedList* body, std::vector<Token*> paramTokens, Token* returnToken);
	Function(string naam, string params, LinkedList* body, std::vector<Token*> paramTokens, Token* returnToken, bool userdef);
	std::string getName() { return _naam; };
	std::string getParams() { return _params; };
	std::vector<Token*> getParamTokens() { return _paramTokens; };
	Token* getReturn() { return _returnToken; };
	bool		isUserdef() { return _userdef; };
	LinkedList* getBody() {
		return _body;
	};
	~Function();
};


class FunctionHandler
{
private:
	FunctionHandler() ;
	static bool instanceFlag;
	static FunctionHandler *handler;
	static std::list<Function> functions;
	~FunctionHandler();
public:
		#ifdef _WIN32 //vanwege apple noobs
	void FunctionHandler::addFunction(Function func);
		#else
	void addFunction(Function func);
		#endif

	static FunctionHandler *getInstance();
	std::list<Function> getFunctions();
};

