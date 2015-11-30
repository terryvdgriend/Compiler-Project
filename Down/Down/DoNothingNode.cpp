#include "stdafx.h"
#include "DoNothingNode.h"

void DoNothingNode::show()
{
	cout << "Do Nothing." << endl;
}

void DoNothingNode::action()
{
	//
}

void DoNothingNode::accept(NodeVisitor& visitor)
{
	visitor.visit(*this);
}