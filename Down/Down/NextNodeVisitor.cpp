#include "stdafx.h"
#include "NextNodeVisitor.h"

NextNodeVisitor::NextNodeVisitor(VirtualMachine* vm)
{
	this->vm = vm;
}

NextNodeVisitor::~NextNodeVisitor()
{
	delete nextNode;
}

void NextNodeVisitor::visit(ConditionalJumpNode& node)
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

void NextNodeVisitor::visit(DirectFunctionCall* node)
{
	nextNode = (*node).getNext();
}

void NextNodeVisitor::visit(DoNothingNode* node)
{
	nextNode = (*node).getNext();
}

void NextNodeVisitor::visit(FunctionCall* node)
{
	nextNode = (*node).getNext();
}

void NextNodeVisitor::visit(JumpGotoNode* node)
{
	nextNode = (*node).getNext();
}