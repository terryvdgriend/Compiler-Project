#pragma once
#include "Token.h"

class LinkedTokenList
{
	public:
		LinkedTokenList();
		LinkedTokenList(shared_ptr<LinkedTokenList>& other);

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
		weak_ptr<Token> _last;
};