#pragma once
#include "AbstractFunctionCall.h"

class NextNodeVisitor;

class DirectFunctionCall : public AbstractFunctionCall
{
	public:
		void show();
		void action();
		void accept(NextNodeVisitor& visitor);
};