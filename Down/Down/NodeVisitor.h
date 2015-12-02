#pragma once
#include "ActionNode.h"
#include "VirtualMachine.h"

class ConditionalJumpNode;
class DirectFunctionCall;
class DoNothingNode;
class FunctionCall;
class JumpGoToNode;
class SwitchNode;

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
		unique_ptr<VirtualMachine> vm;
		shared_ptr<ActionNode> nextNode;
};