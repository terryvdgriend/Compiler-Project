#include "stdafx.h"
#include "JumpGotoNode.h"

void JumpGotoNode::show()
{
	cout << "Jump and go to. \n";
}

void JumpGotoNode::action()
{
	//
}

void JumpGotoNode::accept(NodeVisitor& visitor)
{
	visitor.visit(*this);
}