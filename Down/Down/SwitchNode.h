#pragma once
#include "ActionNode.h"
#include "LinkedActionList.h"

class SwitchNode : public ActionNode
{
	public:
		SwitchNode();

		void show();
		void accept(shared_ptr<NodeVisitor>& visitor);

		shared_ptr<LinkedActionList> getDefaultNodeList();
		shared_ptr<LinkedActionList> getSwitchConditionList();
		void setSwitchConditionList(shared_ptr<LinkedActionList> value);
		map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>>& getJumpMap();

	private:
		shared_ptr<LinkedActionList> defaultNodeList;
		shared_ptr<LinkedActionList> switchConditionList;
		map<shared_ptr<LinkedActionList>, shared_ptr<LinkedActionList>> jumpMap;
};