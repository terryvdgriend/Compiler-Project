#pragma once
#include "ActionNode.h"

class JumpGoToNode : public ActionNode
{
	public:
		ActionNode* getJumpToNode(){ return jumpToNode; };
		void setJumpToNode(ActionNode* value){ jumpToNode = value; };
		void show();
		void action();
		void accept(NodeVisitor& visitor);
	private:
		ActionNode* jumpToNode;
};