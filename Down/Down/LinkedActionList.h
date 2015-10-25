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
	~LinkedActionList();
};

