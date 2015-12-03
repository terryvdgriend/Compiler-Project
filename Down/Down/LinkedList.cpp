#include "stdafx.h"
#include "LinkedList.h"

LinkedList::LinkedList()
{
	_first	= nullptr;
	_last	= nullptr;
	_count	= 0;
}

LinkedList::LinkedList(shared_ptr<LinkedList>& other) 
{
	_first	= nullptr;
	_last	= nullptr;
	_count	= 0;
	vector<shared_ptr<Token>> partners;
	shared_ptr<Token> current = other->getFirst();

	while (current != nullptr) 
	{
		shared_ptr<Token> nToken = current;

		if (nToken->getPartner() != nullptr) 
		{
			bool partnerFound = false;

			for (shared_ptr<Token> p : partners)
			{
				if (Token::compare(p, nToken->getPartner())) 
				{
					p->setPartner(nToken);
					nToken->setPartner(p);
					partnerFound = true;

					break;
				}
			}
			if (!partnerFound) 
			{
				partners.push_back(nToken);
			}
		}
		add(nToken);
		current = current->getNext();
	}
}

void LinkedList::add(shared_ptr<Token> token)
{
	insertLast(token);
}

void LinkedList::insertLast(shared_ptr<Token> token)
{
	if (token != nullptr)
	{
		_count++;

		if (_first == nullptr)
		{
			_first = _last = token;
		}
		else
		{
			_last->setNext(token);
			token->setPrevious(_last);
			_last = token;
		}
	}
}

int LinkedList::getSize()
{
	return _count;
}

shared_ptr<Token> LinkedList::getFirst()
{
	return _first;
}

void LinkedList::setFirst(shared_ptr<Token> first)
{
	_first = first;
}

shared_ptr<Token> LinkedList::getLast()
{
	return _last;
}

void LinkedList::setLast(shared_ptr<Token> last)
{
	_last = last;
}