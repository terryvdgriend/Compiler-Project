#include "stdafx.h"
#include "SwitchNode.h"


SwitchNode::SwitchNode()
{
	defaultNodeList = new LinkedActionList();
	switchCondition = nullptr;
}

void SwitchNode::show() 
{
	cout << "Switch jump. \n";
}

void SwitchNode::accept(NodeVisitor & visitor)
{
	visitor.visit(*this);
}

void SwitchNode::action()
{
}

SwitchNode::~SwitchNode()
{
}
