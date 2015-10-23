#pragma once
#include "ActionNode.h"
class JumpGotoNode :
	public ActionNode
{
public:
	JumpGotoNode();
	virtual void  Show();
	virtual void  Action();
	virtual void  Accept(NodeVisitor visitor);
	~JumpGotoNode();
};

