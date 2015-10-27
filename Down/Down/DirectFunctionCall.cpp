#include "stdafx.h"
#include "DirectFunctionCall.h"


DirectFunctionCall::DirectFunctionCall() : AbstractFunctionCall()
{
}

void  DirectFunctionCall::Show()
{
	std::cout << "Direct function call: " << getContentArray()[0] << " - " << getContentArray()[1] << " \n";
}

void  DirectFunctionCall::Action()
{

}

void  DirectFunctionCall::Accept(NodeVisitor visitor)
{
	visitor.visit(*this);
}

DirectFunctionCall::~DirectFunctionCall()
{
}
