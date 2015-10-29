#include "stdafx.h"
#include "FunctionCall.h"


FunctionCall::FunctionCall()
{
}

void  FunctionCall::Show()
{
	std::cout << "Function: " << getContentArray()[0] << " " << getContentArray()[1] << " " << getContentArray()[2] << " \n";
}

void  FunctionCall::Action()
{

}

void  FunctionCall::Accept(NodeVisitor visitor)
{
	visitor.visit(*this);
}

FunctionCall::~FunctionCall()
{
}
