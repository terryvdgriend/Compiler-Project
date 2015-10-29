#pragma once
#include "ActionNode.h"

class DoNothingNode : public ActionNode
{
	public:
		void show();
		void action();
		void accept(NodeVisitor& visitor);
};