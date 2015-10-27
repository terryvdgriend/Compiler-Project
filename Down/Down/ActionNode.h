#pragma once
#include "NodeVisitor.h"

class NodeVisitor;

class ActionNode
{
private:
	ActionNode* next;
	ActionNode* previous;
public:
	ActionNode();
	virtual void  Show();
	virtual void  Action();
	virtual void  Accept(NodeVisitor visitor);

	ActionNode* getNext(){ return next; }
	ActionNode* getPrevious(){ return previous; }
	ActionNode* setNext(ActionNode* value) { return this->next = value; }
	ActionNode* setPrevious(ActionNode* value) { return this->previous = value; }
	~ActionNode();
};

