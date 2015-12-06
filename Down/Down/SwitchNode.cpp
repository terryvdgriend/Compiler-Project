#include "stdafx.h"
#include "SwitchNode.h"
#include "MandatoryNodeIncludes.h"

SwitchNode::SwitchNode()
{
	defaultNodeList		= make_shared<LinkedActionList>();
	switchConditionList = nullptr;
}

void SwitchNode::show() 
{
	cout << "Switch Jump." << endl;
}

void SwitchNode::accept(shared_ptr<NodeVisitor>& visitor)
{
	visitor->visit(*this);
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

map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>& SwitchNode::getJumpMap()
{
	return jumpMap;
}