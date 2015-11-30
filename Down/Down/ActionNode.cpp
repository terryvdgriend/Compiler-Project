#include "stdafx.h"
#include "ActionNode.h"

ActionNode::ActionNode()
{
	next		= nullptr;
	previous	= nullptr;
}

shared_ptr<ActionNode> ActionNode::getNext()
{
	return next;
}

shared_ptr<ActionNode> ActionNode::getPrevious()
{
	return previous;
}

shared_ptr<ActionNode> ActionNode::setNext(shared_ptr<ActionNode> value)
{
	return next = value;
}

shared_ptr<ActionNode> ActionNode::setPrevious(shared_ptr<ActionNode> value)
{
	return previous = value;
}