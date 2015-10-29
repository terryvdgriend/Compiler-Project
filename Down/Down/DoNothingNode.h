#pragma once
#include "ActionNode.h"

class NextNodeVisitor;

class DoNothingNode : public ActionNode
{
	public:
		void show();
		void action();
		void accept(NextNodeVisitor& visitor);
};