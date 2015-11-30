#include "stdafx.h"
#include "DirectFunctionCall.h"

void DirectFunctionCall::show()
{
	cout << "Direct Function Call: " << getContentArray()[0] << " - " << getContentArray()[1] << endl;
}

void DirectFunctionCall::action()
{
	//
}

void DirectFunctionCall::accept(NodeVisitor& visitor)
{
	visitor.visit(*this);
}