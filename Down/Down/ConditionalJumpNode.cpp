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
	return nextOnTrue;
}

void ConditionalJumpNode::setOnTrue(shared_ptr<ActionNode> value)
{
	nextOnTrue = value;
}

shared_ptr<ActionNode> ConditionalJumpNode::getOnFalse()
{
	return nextOnFalse;
}

void ConditionalJumpNode::setOnFalse(shared_ptr<ActionNode> value)
{
	nextOnFalse = value;
}