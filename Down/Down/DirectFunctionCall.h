#pragma once
#include "AbstractFunctionCall.h"
class DirectFunctionCall :
	public AbstractFunctionCall
{
public:
	DirectFunctionCall();
	virtual void Show();
	virtual void Action();
	virtual void Accept(NodeVisitor visitor);
	~DirectFunctionCall();
};

