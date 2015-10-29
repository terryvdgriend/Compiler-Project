#include "stdafx.h"
#include "DoNothingNode.h"

void DoNothingNode::show()
{
	cout << "Do nothing. \n";
}

void DoNothingNode::action()
{
	//
}

void DoNothingNode::accept(NextNodeVisitor& visitor)
{
	visitor.visit(*this);
}