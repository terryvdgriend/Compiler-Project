#include "stdafx.h"
#include "DirectFunctionCall.h"


DirectFunctionCall::DirectFunctionCall() : AbstractFunctionCall()
{
}

void  DirectFunctionCall::Show()
{

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
