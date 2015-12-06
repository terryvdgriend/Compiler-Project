#pragma once
#include "ActionNode.h"

class ConditionalJumpNode :	public ActionNode
{
	public:
		void show();
		void accept(shared_ptr<NodeVisitor>& visitor);

		shared_ptr<ActionNode> getOnTrue();
		void setOnTrue(shared_ptr<ActionNode> value);
		shared_ptr<ActionNode> getOnFalse();
		void setOnFalse(shared_ptr<ActionNode> value);
		
	private:
		shared_ptr<ActionNode> nextOnTrue;
		shared_ptr<ActionNode> nextOnFalse;
};