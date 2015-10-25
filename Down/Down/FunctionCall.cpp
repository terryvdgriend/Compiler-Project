#include "stdafx.h"
#include "FunctionCall.h"


FunctionCall::FunctionCall()
{
}

void  FunctionCall::Show()
{

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
