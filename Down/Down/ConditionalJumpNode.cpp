#include "stdafx.h"
#include "ConditionalJumpNode.h"

void ConditionalJumpNode::show()
{
	cout << "Conditional jump. \n";
}

void ConditionalJumpNode::action()
{
	//
}

void ConditionalJumpNode::accept(NodeVisitor& visitor)
{
	visitor.visit(*this);
}