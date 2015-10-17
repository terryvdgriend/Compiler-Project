#include "stdafx.h"
#include "AbstractFuntionCall.h"


AbstractFuntionCall::AbstractFuntionCall()
{
}

void  AbstractFuntionCall::Show()
{

}

void  AbstractFuntionCall::Action()
{

}

void  AbstractFuntionCall::Accept(NodeVisitor visitor)
{
	visitor.visit(*this);
}


AbstractFuntionCall::~AbstractFuntionCall()
{
}
