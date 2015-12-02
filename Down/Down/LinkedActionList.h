#pragma once
#include "ActionNode.h"

class LinkedActionList
{
	public:
		LinkedActionList();
		LinkedActionList(const LinkedActionList &other);
		~LinkedActionList();
		ActionNode* insertBefore(ActionNode* right, ActionNode* value);
		ActionNode * insertBefore(ActionNode * right, LinkedActionList * value);
		ActionNode* insertLast(ActionNode* value);
		ActionNode* add(ActionNode* value);
		ActionNode* add(LinkedActionList* list);
		ActionNode* getFirst(){ return first; };
		ActionNode* getLast(){ return last; };
		int Count() { return count; };
		void printList();

	private:
		int count;
		ActionNode* first;
		ActionNode* last;
};