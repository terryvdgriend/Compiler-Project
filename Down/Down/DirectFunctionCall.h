#pragma once
#include "AbstractFunctionCall.h"

class DirectFunctionCall : public AbstractFunctionCall
{
	public:
		void show();
		void action();
		void accept(NodeVisitor& visitor);
};