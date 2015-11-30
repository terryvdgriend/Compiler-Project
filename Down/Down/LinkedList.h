#pragma once
#include "Token.h"
class LinkedList
{
public:
	LinkedList();
	LinkedList(LinkedList & other);
	~LinkedList();
	void add(Token* value);
	void insertLast(Token* value);
	int size() { return count; };
	Token* first;
	Token* last;
private:

	int count;
};

