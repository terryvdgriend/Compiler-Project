#pragma once
#include "AbstractFunctionCall.h"
class FunctionCall :
	public AbstractFunctionCall
{
public:
	FunctionCall();
	virtual void Show();
	virtual void Action();
	virtual void Accept(NodeVisitor visitor);
	~FunctionCall();

};

