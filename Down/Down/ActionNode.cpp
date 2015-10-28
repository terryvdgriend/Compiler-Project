#include "stdafx.h"
#include "ActionNode.h"


ActionNode::ActionNode()
{
	this->next = nullptr;
	this->previous = nullptr;
}

void  ActionNode::Show()
{

}

void  ActionNode::Action()
{

}

void  ActionNode::Accept(NodeVisitor visitor)
{
	visitor.visit(*this);
}

/*
ActionNode  Next(){
	return nullptr;
}
ActionNode  Previous(){
	return nullptr;
}*/


ActionNode::~ActionNode()
{
}
