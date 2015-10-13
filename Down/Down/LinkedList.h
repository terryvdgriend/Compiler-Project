#pragma once
#include "Token.h"
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	void add(Token* value);
	void insertLast(Token* value);
	int size() { return count; };
	Token* first;
	Token* last;
private:

	int count;
};

