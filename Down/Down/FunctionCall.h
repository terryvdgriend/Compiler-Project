#pragma once
#include "AbstractFunctionCall.h"

class FunctionCall : public AbstractFunctionCall
{
	public:
		void show();
		void accept(shared_ptr<NodeVisitor>& visitor);
};