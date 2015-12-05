#pragma once

class NodeVisitor;

class ActionNode
{
	public:
		ActionNode();

		shared_ptr<ActionNode> getNext();
		shared_ptr<ActionNode> setNext(shared_ptr<ActionNode> value);
		shared_ptr<ActionNode> getPrevious();
		shared_ptr<ActionNode> setPrevious(shared_ptr<ActionNode> value);

		virtual void show() = 0;
		virtual void accept(shared_ptr<NodeVisitor>& visitor) = 0;

	private:
		shared_ptr<ActionNode> next;
		shared_ptr<ActionNode> previous;
};