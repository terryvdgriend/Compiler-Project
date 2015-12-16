#pragma once
#include "AbstractFunctionCall.h"

class DirectFunctionCall : public AbstractFunctionCall
{
	public:
		DirectFunctionCall();
		DirectFunctionCall(shared_ptr<Token>& token);

		void show();
		void accept(shared_ptr<NodeVisitor>& visitor);
};