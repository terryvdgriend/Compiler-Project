#pragma once
#include "ActionNode.h"

class LinkedActionList
{
private:
	int count;
	ActionNode* first;
	ActionNode* last;
public:
	LinkedActionList();
	ActionNode* insertBefore(ActionNode* right, ActionNode* value);
	ActionNode* insertLast(ActionNode* value);
	ActionNode* add(ActionNode* value);
	ActionNode* add(LinkedActionList* list);
	ActionNode* getFirst(){ return first; };
	ActionNode* getLast(){ return last; };
	int Count() { return count; };
	~LinkedActionList();
};

