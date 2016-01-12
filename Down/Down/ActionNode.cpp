#include "stdafx.h"
#include "ActionNode.h"

ActionNode::ActionNode()
{
	_next		= nullptr;
	_previous.reset();
}

shared_ptr<ActionNode> ActionNode::getNext()
{
	return _next;
}

shared_ptr<ActionNode> ActionNode::setNext(shared_ptr<ActionNode> value)
{
	return _next = value;
}

shared_ptr<ActionNode> ActionNode::getPrevious()
{
	if (shared_ptr<ActionNode> n = _previous.lock())
	{
		return n;
	}

	return nullptr;
}

shared_ptr<ActionNode> ActionNode::setPrevious(shared_ptr<ActionNode> value)
{
	_previous = value;

	if (shared_ptr<ActionNode> n = _previous.lock())
	{
		return n;
	}

	return nullptr;
}