#pragma once
#include "Error.h"
#include "Token.h"

class ErrorHandler
{
	public:
		static shared_ptr<ErrorHandler> getInstance();
		list<shared_ptr<Error>>& getErrors();
		void printErrors();
		string asJson();

		void addError();
		void addError(string errorName, ErrorLocation errorLocation);
		void addError(shared_ptr<Error>& error);
		void addError(string errorName, shared_ptr<Token>& token);
		void addError(shared_ptr<Error>& error, IToken expected, IToken result);
    
	private:
		static shared_ptr<ErrorHandler> handler;
		list<shared_ptr<Error>> errors;

		ErrorHandler();
};