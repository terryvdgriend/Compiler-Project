#include "stdafx.h"
#include "DirectFunctionCall.h"

void DirectFunctionCall::show()
{
	cout << "Direct function call: " << getContentArray()[0] << " - " << getContentArray()[1] << " \n";
}

void DirectFunctionCall::action()
{
	//
}

void DirectFunctionCall::accept(NodeVisitor& visitor)
{
	visitor.visit(*this);
}