#pragma once
#include "VirtualMachine.h"
#include "NodeVisitor.h"

class NextNodeVisitor : public NodeVisitor
{
	public:
		NextNodeVisitor(VirtualMachine* vm);
		~NextNodeVisitor();
		void visit(ConditionalJumpNode node);
		//void visit(DirectFunctionCallNode node);
		void visit(DoNothingNode node);
		//void visit(FunctionCallNode node);
		void visit(JumpGotoNode node);
		ActionNode* nextNode;

	private:
		VirtualMachine* vm;
};