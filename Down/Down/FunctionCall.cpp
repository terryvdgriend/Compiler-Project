#include "stdafx.h"
#include "FunctionCall.h"

void FunctionCall::show()
{
	std::cout << "Function: " << getContentArray()[0] << " " << getContentArray()[1] << " " << getContentArray()[2] << " \n";
}

void FunctionCall::action()
{
	//
}

void FunctionCall::accept(NodeVisitor& visitor)
{
	visitor.visit(*this);
}
