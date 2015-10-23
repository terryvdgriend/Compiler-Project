#pragma once
#include "ActionNode.h"
class DoNothingNode :
	public ActionNode
{
public:
	DoNothingNode();
	virtual void  Show();
	virtual void  Action();
	virtual void  Accept(NodeVisitor visitor);
	~DoNothingNode();
};

