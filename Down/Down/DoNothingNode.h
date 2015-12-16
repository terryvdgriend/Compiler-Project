#pragma once
#include "ActionNode.h"

class DoNothingNode : public ActionNode
{
	public:
		void show();
		void accept(shared_ptr<NodeVisitor>& visitor);
};