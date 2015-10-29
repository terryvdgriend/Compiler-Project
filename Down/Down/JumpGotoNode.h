#pragma once
#include "ActionNode.h"

class NextNodeVisitor;

class JumpGotoNode : public ActionNode
{
	private:
		ActionNode* jumpToNode;
	public:
		ActionNode* getJumpToNode(){ return jumpToNode; };
		void setJumpToNode(ActionNode* value){ jumpToNode = value; };
		void show();
		void action();
		void accept(NextNodeVisitor& visitor);	
};