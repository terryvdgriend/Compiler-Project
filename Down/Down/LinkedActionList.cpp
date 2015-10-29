#include "stdafx.h"
#include "LinkedActionList.h"


LinkedActionList::LinkedActionList()
{
	this->count = 0;
	this->first = nullptr;
	this->last = nullptr;
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
	if (right == nullptr)
		return this->insertLast(value);
	else{
		ActionNode* left = right->getPrevious();
		count++;
		value->setNext(right);
		right->setPrevious(value);
		if (left == nullptr)
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

void LinkedActionList::printList(){
	ActionNode* current = first;
	while (current != nullptr){
		current->show();
		current = current->getNext();
	}
}

LinkedActionList::~LinkedActionList()
{
	ActionNode* iter = this->first;
	while (iter != nullptr){
		ActionNode* current = iter;
		iter = iter->getNext();
		delete current;
	}
}


