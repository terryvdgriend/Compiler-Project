#pragma once
#include "ActionNode.h"
class JumpGotoNode :
	public ActionNode
{
private:
	ActionNode* jumpToNode;
public:
	ActionNode* getJumpToNode(){ return jumpToNode; };
	void setJumpToNode(ActionNode* value){ jumpToNode = value; };
	JumpGotoNode();
	virtual void  Show();
	virtual void  Action();
	virtual void  Accept(NodeVisitor visitor);
	~JumpGotoNode();
};

