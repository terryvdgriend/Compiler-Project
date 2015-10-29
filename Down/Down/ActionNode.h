#pragma once

class NodeVisitor;

class ActionNode
{
	public:
		ActionNode();
		~ActionNode();
		ActionNode* getNext() { return next; }
		ActionNode* getPrevious() { return previous; }
		ActionNode* setNext(ActionNode* value) { return this->next = value; }
		ActionNode* setPrevious(ActionNode* value) { return this->previous = value; }
		virtual void show() = 0;
		virtual void action() = 0;
		virtual void accept(NodeVisitor& visitor) = 0;

	private:
		ActionNode* next;
		ActionNode* previous;
};