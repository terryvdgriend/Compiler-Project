#include "stdafx.h"
#include "FunctionCall.h"

void FunctionCall::show()
{
	if (getContentArray().size() > 2)
	{
		std::cout << "Function: " << getContentArray()[0] << " " << getContentArray()[1] << " " << getContentArray()[2] << " \n";
	}
	else
	{
		std::cout << "Function: " << getContentArray()[0] << " " << getContentArray()[1] << " " << " \n";
	}
}

void FunctionCall::action()
{
	//
}

void FunctionCall::accept(NodeVisitor& visitor)
{
	visitor.visit(*this);
}
