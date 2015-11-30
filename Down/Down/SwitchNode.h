#pragma once
#include "ActionNode.h"
#include "LinkedActionList.h"
#include "NodeVisitor.h"

class SwitchNode : public ActionNode
{
	public:
		SwitchNode();

		void show();
		void action();
		void accept(NodeVisitor& visitor);

		shared_ptr<LinkedActionList> getDefaultNodeList();
		shared_ptr<LinkedActionList> getSwitchConditionList();
		void setSwitchConditionList(shared_ptr<LinkedActionList> value);
		shared_ptr<map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>> getJumpMap();

	private:
		shared_ptr<LinkedActionList> defaultNodeList;
		shared_ptr<LinkedActionList> switchConditionList;
		shared_ptr<map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>> jumpMap;
};