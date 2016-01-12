#include "stdafx.h"
#include "JumpGoToNode.h"
#include "MandatoryNodeIncludes.h"

void  JumpGoToNode::show()
{
	cout << "JumpGoToNode. Jumps to ";

	if (shared_ptr<ActionNode> n = _jumpToNode.lock())
	{
		n->show();
	}
}

void JumpGoToNode::accept(shared_ptr<NodeVisitor>& visitor)
{
	visitor->visit(*this);
}

shared_ptr<ActionNode> JumpGoToNode::getJumpToNode()
{
	if (shared_ptr<ActionNode> n = _jumpToNode.lock())
	{
		return n;
	}

	return nullptr;
}

void JumpGoToNode::setJumpToNode(shared_ptr<ActionNode> value)
{
	_jumpToNode = value;
}