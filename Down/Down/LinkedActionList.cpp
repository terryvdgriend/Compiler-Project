#include "stdafx.h"
#include "LinkedActionList.h"

LinkedActionList::LinkedActionList()
{
	count		= 0;
	_firstNode	= nullptr;
	_lastNode.reset();
}

shared_ptr<ActionNode> LinkedActionList::add(shared_ptr<ActionNode> value)
{
	return insertLast(value);
}

shared_ptr<ActionNode> LinkedActionList::add(shared_ptr<LinkedActionList> list)
{
	if (list != nullptr)
	{
		shared_ptr<ActionNode> current = list->_firstNode;

		if (current == nullptr)
		{
			insertLast(current);
		}
		else
		{
			while (current != nullptr)
			{
				insertLast(current);
				current = current->getNext();
			}
		}

		if (shared_ptr<ActionNode> n = _lastNode.lock())
		{
			return n;
		}

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

shared_ptr<ActionNode> LinkedActionList::insertBefore(shared_ptr<ActionNode> right, shared_ptr<ActionNode> value)
{
	if (right == nullptr)
	{
		return insertLast(value);
	}
	else
	{
		shared_ptr<ActionNode> left = right->getPrevious();
		count++;
		value->setNext(right);
		right->setPrevious(value);

		if (left == nullptr)
		{
			_firstNode = value;
		}
		else
		{
			left->setNext(value);
			value->setPrevious(left);
		}

		return value;
	}
}

shared_ptr<ActionNode> LinkedActionList::insertBefore(shared_ptr<ActionNode> right, shared_ptr<LinkedActionList> list)
{
	shared_ptr<ActionNode> current;

	if (list != nullptr) 
	{
		if (right == nullptr) 
		{
			current = list->_firstNode;

			while (current != nullptr) 
			{
				insertLast(current);
				current = current->getNext();
			}

			if (shared_ptr<ActionNode> n = _lastNode.lock())
			{
				return n;
			}

			return nullptr;
		}
		else 
		{
			current = list->_firstNode;
			shared_ptr<ActionNode> value;
			shared_ptr<ActionNode> left;

			while (current != nullptr) 
			{
				value = current;
				current = current->getNext();
				left = right->getPrevious();
				count++;
				value->setNext(right);
				right->setPrevious(value);

				if (left == nullptr)
				{
					_firstNode = value;
				}
				else 
				{
					left->setNext(value);
					value->setPrevious(left);
				}
			}

			return right->getPrevious();
		}
	}
	else 
	{
		return right;
	}
}

shared_ptr<ActionNode> LinkedActionList::insertLast(shared_ptr<ActionNode> value)
{
	if (value != nullptr)
	{
		count++;

		if (_firstNode == nullptr)
		{
			_firstNode = value;
			_lastNode = value;
		}
		else
		{
			if (shared_ptr<ActionNode> n = _lastNode.lock())
			{
				n->setNext(value);
				value->setPrevious(n);
				_lastNode = value;
			}
		}
	}

	return value;
}

void LinkedActionList::printList()
{
	shared_ptr<ActionNode> currentNode = _firstNode;

	while (currentNode != nullptr)
	{
		currentNode->show();
		currentNode = currentNode->getNext();
	}
}

int LinkedActionList::getCount()
{
	return count;
}

shared_ptr<ActionNode> LinkedActionList::getFirst()
{
	return _firstNode;
}

shared_ptr<ActionNode> LinkedActionList::getLast()
{
	if (shared_ptr<ActionNode> n = _lastNode.lock())
	{
		return n;
	}

	return nullptr;
}