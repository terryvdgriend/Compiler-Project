#include "stdafx.h"
#include "ConditionalJumpNode.h"
#include "MandatoryNodeIncludes.h"

void ConditionalJumpNode::show()
{
	cout << "Conditional Jump." << endl;
}

void ConditionalJumpNode::accept(shared_ptr<NodeVisitor>& visitor)
{
	visitor->visit(*this);
}

shared_ptr<ActionNode> ConditionalJumpNode::getOnTrue()
{
	if (shared_ptr<ActionNode> n = _nextOnTrue.lock())
	{
		return n;
	}

	return nullptr;
}

void ConditionalJumpNode::setOnTrue(shared_ptr<ActionNode> value)
{
	_nextOnTrue = value;
}

shared_ptr<ActionNode> ConditionalJumpNode::getOnFalse()
{
	if (shared_ptr<ActionNode> n = _nextOnFalse.lock())
	{
		return n;
	}

	return nullptr;
}

void ConditionalJumpNode::setOnFalse(shared_ptr<ActionNode> value)
{
	_nextOnFalse = value;
}