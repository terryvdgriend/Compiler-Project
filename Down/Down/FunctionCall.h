#pragma once
#include "AbstractFunctionCall.h"

class FunctionCall : public AbstractFunctionCall
{
	public:
		void show();
		FunctionCall(shared_ptr<Token>& token);
		void accept(shared_ptr<NodeVisitor>& visitor);
};