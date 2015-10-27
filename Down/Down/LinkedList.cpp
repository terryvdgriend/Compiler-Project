#include "stdafx.h"
#include "LinkedList.h"


LinkedList::LinkedList()
{
	first = nullptr;
	last = nullptr;
	count = 0;
}

void LinkedList::add(Token* value){
	LinkedList::insertLast(value);
}

void LinkedList::insertLast(Token* value){
	if (value != nullptr){
		count++;
		if (first == nullptr){
			first = last = value;
		}
		else{
			last->next = value;
			value->previous = last;
			last = value;
		}
	}
}


LinkedList::~LinkedList()
{
}
