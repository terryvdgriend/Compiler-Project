#include "stdafx.h"
#include "JumpGoToNode.h"

void  JumpGoToNode::show()
{
	cout << "JumpGoToNode. Jumps to ";
	jumpToNode->show();
}

void JumpGoToNode::accept(shared_ptr<NodeVisitor>& visitor)
{
	visitor->visit(*this);
}

shared_ptr<ActionNode> JumpGoToNode::getJumpToNode()
{
	return jumpToNode;
}

void JumpGoToNode::setJumpToNode(shared_ptr<ActionNode> value)
{
	jumpToNode = value;
}