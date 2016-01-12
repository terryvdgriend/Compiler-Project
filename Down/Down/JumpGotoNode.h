#pragma once
#include "ActionNode.h"

class JumpGoToNode : public ActionNode
{
	public:
		void show();
		void accept(shared_ptr<NodeVisitor>& visitor);

		shared_ptr<ActionNode> getJumpToNode();
		void setJumpToNode(shared_ptr<ActionNode> value);

	private:
		weak_ptr<ActionNode> _jumpToNode;
};