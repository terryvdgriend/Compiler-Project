#include "stdafx.h"
#include "DoNothingNode.h"


DoNothingNode::DoNothingNode()
{
}


void  DoNothingNode::Show()
{
	std::cout << "Do nothing. \n";
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
