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

void NextNodeVisitor::visit(ConditionalJumpNode node)
{
	if ((*vm).getReturnValue() == "true")
	{
		// nextNode = node.nextOnTrue;
	}
	else if ((*vm).getReturnValue() == "false")
	{
		// nextNode = node.nextOnFalse;
	}
}

//void NextNodeVisitor::visit(DirectFunctionCallNode node)
//{
//	nextNode = node.getNext();
//}

void NextNodeVisitor::visit(DoNothingNode node)
{
	nextNode = node.getNext();
}

//void NextNodeVisitor::visit(FunctionCallNode node)
//{
//	nextNode = node.getNext();
//}

void NextNodeVisitor::visit(JumpGotoNode node)
{
	nextNode = node.getNext();
}