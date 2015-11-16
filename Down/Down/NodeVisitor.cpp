#include "stdafx.h"
#include "NodeVisitor.h"
#include "ConditionalJumpNode.h"
#include "DirectFunctionCall.h"
#include "DoNothingNode.h"
#include "FunctionCall.h"
#include "JumpGoToNode.h"
#include "SwitchNode.h"

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
	if ((*vm).getReturnValue() == "true" || (*vm).getReturnValue() == "false") {
		if ((*vm).getReturnValue() == "true")
		{
			nextNode = node.getOnTrue();
		}
		else if ((*vm).getReturnValue() == "false")
		{
			nextNode = node.getOnFalse();
		}
	}
	else {
		if ((*vm).isAnIdentifier((*vm).getReturnValue())) {
			string value = (*vm).getVariable((*vm).getFunctionParametersByValue((*vm).getReturnValue()).back())->getValue();
			if (value == "true")
			{
				nextNode = node.getOnTrue();
			}
			else if (value == "false")
			{
				nextNode = node.getOnFalse();
			}
			else {
				// throw error;
			}
		}
		else {
			// throw error;
		}

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
	nextNode = node.getJumpToNode();
}

void NodeVisitor::visit(SwitchNode& node)
{
	if (node.jumpMap.size() > 0)
	{
		(*vm).execute(*node.switchCondition);
		string value;
		if ((*vm).isAnIdentifier((*vm).getReturnValue()))
		{
			value = (*vm).getVariable((*vm).getFunctionParametersByValue((*vm).getReturnValue()).back())->getValue();
		}
		else 
		{
			value = (*vm).getReturnValue();
		}
		for (auto p = node.jumpMap.begin(); p != node.jumpMap.end(); ++p) 
		{
			(*vm).execute(*p->first);
			if (value == (*vm).getReturnValue()) 
			{
				nextNode = p->second->getFirst();
				return;
			}
		}
		if (node.defaultNodeList->Count() > 0) {
			nextNode = node.defaultNodeList->getFirst();
		}
		else {
			nextNode = node.getNext();
		}
	}
	else {
		nextNode = node.defaultNodeList->getFirst();
	}
}
