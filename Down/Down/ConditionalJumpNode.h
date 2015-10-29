#pragma once
#include "ActionNode.h"

class NextNodeVisitor;

class ConditionalJumpNode :	public ActionNode
{
	public:
		void setOnTrue(ActionNode* value){ nextOnTrue = value; };
		void setOnFalse(ActionNode* value){ nextOnTrue = value; };
		ActionNode* getOnTrue(){ return nextOnTrue; };
		ActionNode* getOnFalse(){ return nextOnFalse; };
		void show();
		void action();
		void accept(NextNodeVisitor& visitor);

	private:
		ActionNode* nextOnTrue;
		ActionNode* nextOnFalse;
};