#pragma once
#include "AbstractFunctionCall.h"

class FunctionCall : public AbstractFunctionCall
{
	public:
		void show();
		void action();
		void accept(NodeVisitor& visitor);
};