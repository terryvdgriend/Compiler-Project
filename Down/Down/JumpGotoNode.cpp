#include "stdafx.h"
#include "JumpGoToNode.h"

void  JumpGoToNode::show()
{
	cout << "JumpGoToNode. Jumps to ";
	jumpToNode->show();
}

void  JumpGoToNode::action()
{
	//
}

void JumpGoToNode::accept(NodeVisitor& visitor)
{
	visitor.visit(*this);
}
