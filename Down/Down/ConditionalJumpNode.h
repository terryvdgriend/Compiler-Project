#pragma once
#include "ActionNode.h"
class ConditionalJumpNode :	public ActionNode
{
private:
	ActionNode* nextOnTrue;
	ActionNode* nextOnFalse;
public:
	void setOnTrue(ActionNode* value){ nextOnTrue = value; };
	void setOnFalse(ActionNode* value){ nextOnTrue = value; };
	ActionNode* getOnTrue(){ return nextOnTrue; };
	ActionNode* getOnFalse(){ return nextOnFalse; };
	ConditionalJumpNode();
	virtual void  Show();
	virtual void  Action();
	virtual void  Accept(NodeVisitor visitor);
	~ConditionalJumpNode();
};

