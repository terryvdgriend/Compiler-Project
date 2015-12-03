#pragma once
#include "Token.h"

class LinkedList
{
	public:
		LinkedList();
		LinkedList(shared_ptr<LinkedList>& other);

		void add(shared_ptr<Token> token);
		void insertLast(shared_ptr<Token> token);

		int getSize();
		shared_ptr<Token> getFirst();
		void setFirst(shared_ptr<Token> token);
		shared_ptr<Token> getLast();
		void setLast(shared_ptr<Token> token);

	private:
		int _count;
		shared_ptr<Token> _first;
		shared_ptr<Token> _last;
};