#include "stdafx.h"
#include "FunctionCall.h"


FunctionCall::FunctionCall()
{
}

void  FunctionCall::Show()
{
	std::cout << "Function. \n";
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
