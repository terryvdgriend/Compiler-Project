#include "stdafx.h"
#include "FunctionCall.h"

void FunctionCall::show()
{
	std::cout << "Function. \n";
}

void FunctionCall::action()
{
	//
}

void FunctionCall::accept(NodeVisitor& visitor)
{
	visitor.visit(*this);
}