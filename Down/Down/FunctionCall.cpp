#include "stdafx.h"
#include "FunctionCall.h"
#include "MandatoryNodeIncludes.h"

void FunctionCall::show()
{
	string function;

	for (size_t i = 0; i < getContentArray().size(); i++)
	{
		function += getContentArray()[i] + " ";
	}

	cout << "Function: " << function << endl;
}

void FunctionCall::accept(shared_ptr<NodeVisitor>& visitor)
{
	visitor->visit(*this);
}