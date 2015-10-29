#include "stdafx.h"
#include "ConditionalJumpNode.h"


ConditionalJumpNode::ConditionalJumpNode()
{
}


void  ConditionalJumpNode::Show()
{
	cout << "ConditionalJumpNode. \n";
}

void  ConditionalJumpNode::Action()
{

}

void  ConditionalJumpNode::Accept(NodeVisitor visitor)
{
	visitor.visit(*this);
}


ConditionalJumpNode::~ConditionalJumpNode()
{
}
