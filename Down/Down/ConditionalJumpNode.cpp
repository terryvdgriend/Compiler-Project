#include "stdafx.h"
#include "ConditionalJumpNode.h"

void ConditionalJumpNode::show()
{
	cout << "Conditional Jump." << endl;
}

void ConditionalJumpNode::action()
{
	//
}

void ConditionalJumpNode::accept(NodeVisitor& visitor)
{
	visitor.visit(*this);
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