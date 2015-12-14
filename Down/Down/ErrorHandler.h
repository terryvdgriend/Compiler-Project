#pragma once
#include "Error.h"
#include "Token.h"

class ErrorHandler
{
	public:
		static shared_ptr<ErrorHandler> getInstance();
		list<shared_ptr<Error>>& getErrors();
		void printErrors();
		void clearErrors();
		string asJson();

		void addError();
		void addError(string errorName, ErrorLocation errorLocation);
		void addError(shared_ptr<Error>& error);
		void addError(string errorName, shared_ptr<Token>& token);
		void addError(shared_ptr<Error>& error, IToken expected, IToken result);

		void addThrownError(string errorName);
    
	private:
		static shared_ptr<ErrorHandler> handler;
		list<shared_ptr<Error>> errors;

		ErrorHandler();
};