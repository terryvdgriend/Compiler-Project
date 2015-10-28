#pragma once
#include "ActionNode.h"
#include "ConditionalJumpNode.h"
//#include "DirectFunctionCall.h"
#include "DoNothingNode.h"
//#include "FunctionCallNode.h"
#include "JumpGotoNode.h"

class ActionNode;

class NodeVisitor
{
	public:
		NodeVisitor();
		~NodeVisitor();
		virtual void visit(DoNothingNode node);
		virtual void visit(JumpGotoNode node);
		virtual void visit(ConditionalJumpNode node);
		//virtual void visit(FunctionalCallNode node);
		//virtual void visit(DirectFunctionCallNode node);
};