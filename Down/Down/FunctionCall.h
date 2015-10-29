#pragma once
#include "AbstractFunctionCall.h"

class NextNodeVisitor;

class FunctionCall : public AbstractFunctionCall
{
	public:
		FunctionCall();
		~FunctionCall();
		void show();
		void action();
		void accept(NextNodeVisitor& visitor);
};