#include "stdafx.h"
#include "JumpGoToNode.h"

void JumpGoToNode::show()
{
	cout << "Jump and go to. \n";
}

void JumpGoToNode::action()
{
	//
}

void JumpGoToNode::accept(NodeVisitor& visitor)
{
	visitor.visit(*this);
}