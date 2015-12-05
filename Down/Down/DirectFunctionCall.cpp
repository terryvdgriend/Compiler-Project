#include "stdafx.h"
#include "DirectFunctionCall.h"

DirectFunctionCall::DirectFunctionCall()
{
	// Required default constructor
}

DirectFunctionCall::DirectFunctionCall(shared_ptr<Token>& token)
{
	token = token;
}

void DirectFunctionCall::show()
{
	cout << "Direct Function Call: " << getContentArray()[0] << " - " << getContentArray()[1] << endl;
}

void DirectFunctionCall::accept(shared_ptr<NodeVisitor>& visitor)
{
	visitor->visit(*this);
}