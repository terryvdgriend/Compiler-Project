#include "stdafx.h"
#include "ConditionalJumpNode.h"


ConditionalJumpNode::ConditionalJumpNode()
{
}


void  ConditionalJumpNode::Show()
{

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
