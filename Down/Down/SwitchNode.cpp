#include "stdafx.h"
#include "SwitchNode.h"

SwitchNode::SwitchNode()
{
	defaultNodeList		= make_shared<LinkedActionList>();
	switchConditionList = nullptr;
	jumpMap				= make_shared<map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>>();
}

void SwitchNode::show() 
{
	cout << "Switch Jump." << endl;
}

void SwitchNode::action()
{
	//
}

void SwitchNode::accept(NodeVisitor & visitor)
{
	visitor.visit(*this);
}

shared_ptr<LinkedActionList> SwitchNode::getDefaultNodeList()
{
	return defaultNodeList;
}

shared_ptr<LinkedActionList> SwitchNode::getSwitchConditionList()
{
	return switchConditionList;
}

void SwitchNode::setSwitchConditionList(shared_ptr<LinkedActionList> value)
{
	switchConditionList = value;
}

shared_ptr<map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>> SwitchNode::getJumpMap()
{
	return jumpMap;
}