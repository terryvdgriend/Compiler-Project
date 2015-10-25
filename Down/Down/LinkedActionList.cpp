#include "stdafx.h"
#include "LinkedActionList.h"


LinkedActionList::LinkedActionList()
{
	this->count = 0;
}

ActionNode* LinkedActionList::insertBefore(ActionNode* right, ActionNode* value){
	return nullptr;
}

ActionNode* LinkedActionList::insertLast(ActionNode* value){
	if (value != nullptr){
		this->count++;
		if (first != nullptr)
			this->first = this->last = value;
		else{
			this->last->setNext(value);
			value->setPrevious(this->last);
			this->last = value;
		}
	}
	return value;
}

LinkedActionList::~LinkedActionList()
{
}
