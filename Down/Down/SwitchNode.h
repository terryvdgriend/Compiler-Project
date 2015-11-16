#pragma once
#include "ActionNode.h"
#include "LinkedActionList.h"
#include "NodeVisitor.h"
class SwitchNode :
	public ActionNode
{
public:
	SwitchNode();
	~SwitchNode();

	void show();
	void accept(NodeVisitor& visitor);
	void action();
public:
	LinkedActionList* defaultNodeList;
	LinkedActionList* switchCondition;
	std::map<LinkedActionList*, LinkedActionList*> jumpMap;
};

