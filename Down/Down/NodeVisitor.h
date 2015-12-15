#pragma once
#include "NodeVisitorList.h"
#include "VirtualMachine.h"

class NodeVisitor
{
	public:
		NodeVisitor(VirtualMachine& virtualMachine);

		void visit(ConditionalJumpNode& node);
		void visit(DirectFunctionCall& node);
		void visit(DoNothingNode& node);
		void visit(FunctionCall& node);
		void visit(JumpGoToNode& node);
		void visit(SwitchNode& node);

		shared_ptr<ActionNode> getNextNode();

	private:
		VirtualMachine* vm;
		shared_ptr<ActionNode> nextNode;
};