#pragma once
#include "AbstractFunctionCall.h"

class DirectFunctionCall : public AbstractFunctionCall
{
	public:
		DirectFunctionCall(Token& token);
		void show();
		void action();
		void accept(NodeVisitor& visitor);

		Token getToken() { return token; }

	private:
		Token token;
};