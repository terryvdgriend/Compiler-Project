#pragma once
#include "ActionNode.h"
class AbstractFuntionCall :
	public ActionNode
{
public:
	AbstractFuntionCall();
	virtual void  Show();
	virtual void  Action();
	virtual void  Accept(NodeVisitor visitor);
	~AbstractFuntionCall();
};

