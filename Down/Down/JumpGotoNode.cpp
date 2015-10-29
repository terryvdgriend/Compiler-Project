#include "stdafx.h"
#include "JumpGotoNode.h"


JumpGotoNode::JumpGotoNode()
{
}

void  JumpGotoNode::Show()
{
	cout << "JumpGoToNode. Jumps to ";
	jumpToNode->Show();
}

void  JumpGotoNode::Action()
{

}

void  JumpGotoNode::Accept(NodeVisitor visitor)
{
	visitor.visit(*this);
}

JumpGotoNode::~JumpGotoNode()
{
}
