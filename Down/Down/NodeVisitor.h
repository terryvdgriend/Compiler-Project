#pragma once
#include "ActionNode.h"

class ActionNode;

class NodeVisitor
{
public:
	NodeVisitor();
	virtual void  visit(ActionNode node);
	~NodeVisitor();
};

