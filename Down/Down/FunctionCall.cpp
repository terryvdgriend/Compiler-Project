#include "stdafx.h"
#include "FunctionCall.h"

FunctionCall::FunctionCall()
{

}

FunctionCall::~FunctionCall()
{

}

void FunctionCall::show()
{
	std::cout << "Function. \n";
}

void FunctionCall::action()
{
	//
}

void  FunctionCall::accept(NextNodeVisitor& visitor)
{
	visitor.visit(this);
}