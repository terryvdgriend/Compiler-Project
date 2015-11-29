#include "stdafx.h"
#include "LinkedList.h"
#include <algorithm>


LinkedList::LinkedList()
{
	first = nullptr;
	last = nullptr;
	count = 0;
}

LinkedList::LinkedList(LinkedList &other) {
	std::vector<Token*> partners;
	Token* current = other.first;
	while (current != nullptr) {
		Token * nToken = new Token(*current);
		if (nToken->getPartner() != nullptr) {
			bool partnerFound = false;
			for (auto p : partners) {
				if (Token::compare(p,nToken->getPartner())) {
					p->setPartner(nToken);
					nToken->setPartner(p);
					partnerFound = true;
					break;
				}
			}
			if (!partnerFound) {
				partners.push_back(nToken);
			}
		}
		this->add(nToken);
		current = current->next;
	}
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
	Token* iter = this->first;
	while (iter != nullptr){
		Token* current = iter;
			iter = iter->next;
		delete current;
	}
}
