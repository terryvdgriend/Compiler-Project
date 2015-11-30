#include "stdafx.h"
#include "FunctionCall.h"

void FunctionCall::show()
{
	std::string function;
	for (size_t i = 0; i < getContentArray().size(); i++)
	{
		function += getContentArray()[i] + " ";
	}

	std::cout << "Function: " << function << " \n";
}

void FunctionCall::action()
{
	//
}

void FunctionCall::accept(NodeVisitor& visitor)
{
	visitor.visit(*this);
}
