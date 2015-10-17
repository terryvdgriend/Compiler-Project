#pragma once
#include "NodeVisitor.h"

class NodeVisitor;

class ActionNode
{
public:
	ActionNode();
	virtual void  Show();
	virtual void  Action();
	virtual void  Accept(NodeVisitor visitor);

	//virtual ActionNode  Next();
	//virtual ActionNode  Previous();
	~ActionNode();
};

