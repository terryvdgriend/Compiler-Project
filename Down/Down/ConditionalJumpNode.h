#pragma once
#include "ActionNode.h"
class ConditionalJumpNode :	public ActionNode
{
public:
	ConditionalJumpNode();
	virtual void  Show();
	virtual void  Action();
	virtual void  Accept(NodeVisitor visitor);
	~ConditionalJumpNode();
};

