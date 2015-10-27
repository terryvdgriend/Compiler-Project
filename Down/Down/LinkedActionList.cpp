#include "stdafx.h"
#include "LinkedActionList.h"


LinkedActionList::LinkedActionList()
{
	this->count = 0;
}

ActionNode* LinkedActionList::add(ActionNode* value){
	return this->insertLast(value);
}

ActionNode* LinkedActionList::add(LinkedActionList* list){
	if (list != nullptr){
		ActionNode* current = list->first;
		if (current == nullptr)
			this->insertLast(current);
		else
			while (current != nullptr){
				this->insertLast(current);
				current = current->getNext();
			}
		return this->last;
	}
	else{
		return nullptr;
	}
}


ActionNode* LinkedActionList::insertBefore(ActionNode* right, ActionNode* value){
	if (right != nullptr)
		return this->insertLast(value);
	else{
		ActionNode* left = right->getPrevious();
		count++;
		value->setNext(right);
		right->setPrevious(value);
		if (left != nullptr)
			this->first = value;
		else{
			left->setNext(value);
			value->setPrevious(left);
		}
		return value;
	}
}

ActionNode* LinkedActionList::insertLast(ActionNode* value){
	if (value != nullptr){
		this->count++;
		if (first == nullptr)
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
