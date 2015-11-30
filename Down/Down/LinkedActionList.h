#pragma once
#include "ActionNode.h"

class LinkedActionList
{
	public:
		LinkedActionList();
		LinkedActionList(const LinkedActionList& other);

		void printList();

		shared_ptr<ActionNode> add(shared_ptr<ActionNode> value);
		shared_ptr<ActionNode> add(shared_ptr<LinkedActionList> list);
		shared_ptr<ActionNode> insertBefore(shared_ptr<ActionNode> right, shared_ptr<ActionNode> value);
		shared_ptr<ActionNode> insertBefore(shared_ptr<ActionNode> right, shared_ptr<LinkedActionList> value);
		shared_ptr<ActionNode> insertLast(shared_ptr<ActionNode> value);

		int getCount();
		shared_ptr<ActionNode> getFirst();
		shared_ptr<ActionNode> getLast();

	private:
		int count;
		shared_ptr<ActionNode> firstNode;
		shared_ptr<ActionNode> lastNode;
};