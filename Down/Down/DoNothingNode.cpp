#include "stdafx.h"
#include "DoNothingNode.h"
#include "MandatoryNodeIncludes.h"

void DoNothingNode::show()
{
	cout << "Do Nothing." << endl;
}

void DoNothingNode::accept(shared_ptr<NodeVisitor>& visitor)
{
	visitor->visit(*this);
}