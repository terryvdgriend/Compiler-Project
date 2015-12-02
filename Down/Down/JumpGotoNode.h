#pragma once
#include "ActionNode.h"
#include "NodeVisitor.h"

class JumpGoToNode : public ActionNode
{
	public:
		void show();
		void action();
		void accept(NodeVisitor& visitor);

		shared_ptr<ActionNode> getJumpToNode();
		void setJumpToNode(shared_ptr<ActionNode> value);

	private:
		shared_ptr<ActionNode> jumpToNode;
};