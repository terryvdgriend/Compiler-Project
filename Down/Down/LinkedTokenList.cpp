#include "stdafx.h"
#include "LinkedTokenList.h"

LinkedTokenList::LinkedTokenList()
{
	_first	= nullptr;
	_last.reset();
	_count	= 0;
}

LinkedTokenList::LinkedTokenList(shared_ptr<LinkedTokenList>& other)
{
	_first	= nullptr;
	_last.reset();
	_count	= 0;
	vector<shared_ptr<Token>> partners;
	shared_ptr<Token> current = other->getFirst();

	while (current != nullptr) 
	{
		shared_ptr<Token> nToken = make_shared<Token>(current);

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

void LinkedTokenList::add(shared_ptr<Token> token)
{
	insertLast(token);
}

void LinkedTokenList::insertLast(shared_ptr<Token> token)
{
	if (token != nullptr)
	{
		_count++;

		if (_first == nullptr)
		{
			_first = token;
			_last = token;
		}
		else
		{
			if (shared_ptr<Token> t = _last.lock())
			{
				t->setNext(token);
				token->setPrevious(t);
				_last = token;
			}
		}
	}
}

int LinkedTokenList::getSize()
{
	return _count;
}

shared_ptr<Token> LinkedTokenList::getFirst()
{
	return _first;
}

void LinkedTokenList::setFirst(shared_ptr<Token> first)
{
	_first = first;
}

shared_ptr<Token> LinkedTokenList::getLast()
{
	if (shared_ptr<Token> t = _last.lock())
	{
		return t;
	}

	return nullptr;
}

void LinkedTokenList::setLast(shared_ptr<Token> last)
{
	_last = last;
}