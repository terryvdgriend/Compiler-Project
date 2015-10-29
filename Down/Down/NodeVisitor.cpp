#include "stdafx.h"
#include "NodeVisitor.h"
#include "ConditionalJumpNode.h"
#include "DirectFunctionCall.h"
#include "DoNothingNode.h"
#include "FunctionCall.h"
#include "JumpGoToNode.h"

NodeVisitor::NodeVisitor(VirtualMachine& vm) : vm{ &vm }
{
	//
}

NodeVisitor::~NodeVisitor()
{
	delete nextNode;
}

void NodeVisitor::visit(ConditionalJumpNode& node)
{
	if ((*vm).getReturnValue() == "true")
	{
		nextNode = node.getOnTrue();
	}
	else if ((*vm).getReturnValue() == "false")
	{
		nextNode = node.getOnFalse();
	}
}

void NodeVisitor::visit(DirectFunctionCall& node)
{
	nextNode = node.getNext();
}

void NodeVisitor::visit(DoNothingNode& node)
{
	nextNode = node.getNext();
}

void NodeVisitor::visit(FunctionCall& node)
{
	nextNode = node.getNext();
}

void NodeVisitor::visit(JumpGoToNode& node)
{
	nextNode = node.getNext();
}