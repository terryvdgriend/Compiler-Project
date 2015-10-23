#include "stdafx.h"
#include "DoNothingNode.h"


DoNothingNode::DoNothingNode()
{
}


void  DoNothingNode::Show()
{

}

void  DoNothingNode::Action()
{

}

void  DoNothingNode::Accept(NodeVisitor visitor)
{
	visitor.visit(*this);
}

DoNothingNode::~DoNothingNode()
{
}
