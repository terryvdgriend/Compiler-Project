#include "stdafx.h"
#include "LinkedActionList.h"


LinkedActionList::LinkedActionList()
{
	count		= 0;
	firstNode	= nullptr;
	lastNode	= nullptr;
}

shared_ptr<ActionNode> LinkedActionList::add(shared_ptr<ActionNode> value)
{
	return insertLast(value);
}

shared_ptr<ActionNode> LinkedActionList::add(shared_ptr<LinkedActionList> list)
{
	if (list != nullptr)
	{
		shared_ptr<ActionNode> current = list->firstNode;

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

		return lastNode;
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
			firstNode = value;
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
			current = list->firstNode;

			while (current != nullptr) 
			{
				insertLast(current);
				current = current->getNext();
			}

			return lastNode;
		}
		else 
		{
			current = list->firstNode;
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
					firstNode = value;
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

		if (firstNode == nullptr)
		{
			firstNode = lastNode = value;
		}
		else
		{
			lastNode->setNext(value);
			value->setPrevious(lastNode);
			lastNode = value;
		}
	}

	return value;
}

void LinkedActionList::printList()
{
	shared_ptr<ActionNode> currentNode = firstNode;

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
	return firstNode;
}

shared_ptr<ActionNode> LinkedActionList::getLast()
{
	return lastNode;
}